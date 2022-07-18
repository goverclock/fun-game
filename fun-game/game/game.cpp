#include "game.h"
#include "unit.h"
#include "view.h"

Game::Game(View *v) {
    view = v;
    memset(units, 0, sizeof(units));

    cur_opt.type = Packet::game_playeropt;
}

void Game::serv_msg(Packet p) {
    switch(p.type) {
        case Packet::reg_response:
            id = p.pack.reg_success_info.new_id;
            break;
        case Packet::game_start:{
            view->set_game_gui_on_off(true);
            run = true;
            // assume *units[] are all nullptr
            auto &info = p.pack.game_start_info;
            for(int i = 0; info.player_ids[i] != -1; i++) {
                if(units[i] != nullptr) delete units[i];
                units[i] = new Unit(this, info.player_ids[i]);
                units[i]->setPos(info.x[i], info.y[i]);
                view->sce.addItem(units[i]);

                if(info.player_ids[i] == id)
                    clnt_unit = units[i];
            }
            break;
        }
        case Packet::game_your_turn:{
            your_turn = true;
            break;
        }
        case Packet::game_playeropt:{
            // TODO...
            break;
        }
        case Packet::game_end:{
            view->set_game_gui_on_off(false);
            run = false;
            your_turn = false;
            for(int i = 0; i < MAX_CLIENTS; i++)
                if(units[i] != nullptr) {
                    delete units[i];
                    units[i] = nullptr;
                }
            clnt_unit = nullptr;
            break;
        }
    }
}
