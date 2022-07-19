#include "game.h"
#include "fly_object.h"
#include "angle_indicator.h"
#include "unit.h"
#include "view.h"

Game::Game(View *v) {
    view = v;
    memset(units, 0, sizeof(units));

    connect(v->pb, &PowerBar::released, this, &Game::end_turn);
    connect(v->end_turn, &Button::released, this, &Game::end_turn);
}

// send operation packet and end turn
void Game::end_turn() {
    if(!your_turn) return;
    your_turn = false;
    auto &info(cur_opt.pack.game_playeropt_info);
    info.power = view->pb->cur_power;       // power
    info.angle = clnt_unit->ang->angle();   // angle
    emit user_msg(cur_opt);
}

void Game::serv_msg(Packet p) {
    switch (p.type) {
        case Packet::reg_response:
            id = p.pack.reg_success_info.new_id;
            break;
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
            // TODO... summon a FlyObject
            auto &info = p.pack.game_playeropt_info;
            int ind = 0;
            // while( units[ind]->player_id != info.id) ind++;
            
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
