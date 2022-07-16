#include "game.h"

#include "view.h"

Game::Game(View *v) {
    view = v;
    id = view->id;
    memset(units, 0, sizeof(units));

    cur_opt.type = Packet::game_playeropt;
}

void Game::serv_msg(Packet p) {
    switch(p.type) {
        case Packet::game_start:{
            run = true;
            // assume *units[] are all nullptr
            auto &info = p.pack.game_start_info;
            for(int i = 0; info.player_ids[i] != -1; i++) {
                units[i] = new Unit();
                units[i]->player_id = info.player_ids[i];
                units[i]->setPos(info.x[i], info.y[i]);
                view->sce.addItem(units[i]);
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
            run = false;
            your_turn = false;
            for(int i = 0; i < MAX_CLIENTS; i++)
                if(units[i] != nullptr) {
                    delete units[i];
                    units[i] = nullptr;
                }
            break;
        }
    }
}
