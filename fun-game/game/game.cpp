#include "game.h"

#include "angle_indicator.h"
#include "fly_object.h"
#include "unit.h"
#include "view.h"

Game::Game(View *v) {
    view = v;
    memset(units, 0, sizeof(units));

    connect(v->pb, &PowerBar::released, this, &Game::end_turn);
    connect(v->end_turn, &Button::released, [&] {
        cur_opt.pack.game_playeropt_info.pass = true;
        end_turn();
    });

    auto &info(cur_opt.pack.game_playeropt_info);
    // fly button
    connect(view->fly, &Button::clicked, [&] {
        if (your_turn && clnt_unit->energy >= 100) {
            info.fly = true;
            clnt_unit->energy -= 100;
            view->MP->set_text("体力:" + QString::number(clnt_unit->energy));
        }
    });
    // multiple button
    connect(view->multi, &Button::clicked, [&] {
        if (your_turn && clnt_unit->energy >= 60) {
            info.multi = true;
            clnt_unit->energy -= 60;
            view->MP->set_text("体力:" + QString::number(clnt_unit->energy));
        }
    });
    // duplicate button
    connect(view->dupli, &Button::clicked, [&] {
        if (your_turn && clnt_unit->energy >= 40) {
            info.times += 2;
            clnt_unit->energy -= 40;
            view->MP->set_text("体力:" + QString::number(clnt_unit->energy));
        }
    });
    // violence button
    connect(view->violen, &Button::clicked, [&] {
        if (your_turn && clnt_unit->energy >= 40) {
            info.violence++;
            clnt_unit->energy -= 40;
            view->MP->set_text("体力:" + QString::number(clnt_unit->energy));
        }
    });
}

// send operation packet and end turn
void Game::end_turn() {
    if (!your_turn) return;
    your_turn = false;
    auto &info(cur_opt.pack.game_playeropt_info);
    info.id = clnt_unit->player_id;        // id
    info.power = view->pb->cur_power;      // power
    info.angle = clnt_unit->ang->angle();  // angle
    info.times++;                          // basic 1
    emit user_msg(cur_opt);
}

void Game::serv_msg(Packet p) {
    switch (p.type) {
        case Packet::reg_response:
            id = p.pack.reg_success_info.new_id;
            break;

        case Packet::clnt_quit: {
            int quit_id = p.pack.clnt_quit_info.id;
            if (run)
                for (int i = 0; i < MAX_CLIENTS; i++)
                    if (units[i] != nullptr && units[i]->player_id == quit_id) {
                        delete units[i];
                        units[i] = nullptr;
                        break;
                    }
            break;
        }

        case Packet::game_start: {
            view->set_game_gui_on_off(true);
            run = true;
            // assume *units[] are all nullptr
            auto &info = p.pack.game_start_info;
            for (int i = 0; info.player_ids[i] != -1; i++) {
                if (units[i] != nullptr) delete units[i];
                units[i] = new Unit(this, info.player_ids[i]);
                units[i]->setPos(info.x[i], info.y[i]);
                view->sce.addItem(units[i]);

                if (info.player_ids[i] == id) clnt_unit = units[i];
            }
            break;
        }
        case Packet::game_your_turn: {
            view->pb->clear();
            bzero(&cur_opt, sizeof(cur_opt));
            cur_opt.type = Packet::game_playeropt;
            clnt_unit->energy = 100;
            view->MP->set_text("体力:" + QString::number(clnt_unit->energy));
            your_turn = true;
            break;
        }
        case Packet::game_playeropt: {
            auto &info = p.pack.game_playeropt_info;
            int ind = 0;
            while (units[ind]->player_id != info.id) ind++;

            // TODO... summon a FlyObject
            flyobj_resolv(units[ind], p);
            //
            break;
        }
        case Packet::game_end: {
            view->set_game_gui_on_off(false);
            run = false;
            your_turn = false;
            for (int i = 0; i < MAX_CLIENTS; i++)
                if (units[i] != nullptr) {
                    delete units[i];
                    units[i] = nullptr;
                }
            clnt_unit = nullptr;
            break;
        }
    }
}

void Game::flyobj_resolv(Unit *u, Packet p) {
    auto &info = p.pack.game_playeropt_info;
    if (info.pass) return;
    if (info.fly) {
        new FlyObject(u, p);
        return;
    }

    // TODO: gap time between duplicate
    auto pl(p);
    auto pr(p);
    pl.pack.game_playeropt_info.angle += 10;
    pr.pack.game_playeropt_info.angle -= 10;
    int lag = 0;
    while (info.times--) {
        new FlyObject(u, p, lag);
        if (info.multi) {
            new FlyObject(u, pl, lag);
            new FlyObject(u, pr, lag);
        }
        lag += 600;
    }
}
