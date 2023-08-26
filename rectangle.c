#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

int main()
{
    al_init();
    al_init_image_addon();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(640, 480);
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_BITMAP* mysha = al_load_bitmap("mysha.png");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                // game logic goes here.
                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }
        if(done)
            break;

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");

        al_draw_bitmap(mysha, 100, 100, 0);

        al_flip_display();
    }
    al_rest(100);
    al_destroy_bitmap(mysha);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_uninstall_keyboard();
    al_uninstall_mouse();
    return 0;
}
//        if (draw_main_menu)
//        {
//            al_draw_bitmap(Risk_menu, 0, 0, 0);
//            al_flip_display();
//        }
//        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || draw_main_menu) {
//            al_draw_bitmap(Risk_menu, 0, 0, 0);
//            al_flip_display();
//            draw_main_menu = false;
//            if (!main_menu && al_is_event_queue_empty(queue))                                        //Main Menu
//            {
//                //redraw = false;
//                if (event.mouse.button & 1) {
//                    if (curX <= 910 && curX >= 630 && curY <= 510 && curY >= 450)                   // NEW Game
//                    {
//                        main_menu = true;
//                        draw_main_menu = false;
//                        al_destroy_bitmap(Risk_menu);
//                        al_clear_to_color(al_map_rgb(0, 0, 0));
//                        redraw = true;
//                        player_menu = true;
//                    }
//                    //if (curX <= 910 && curX >= 630 && curY <= 625 && curY >= 560);            // Load Game
//                    //{
//                    //  if (bazi save dare){
//                    //      load kon
//                    //  }
//                    //  else if (bazi save nadare)
//                    //  {
//                    //      peygham namayesh bede !
//                    //  }
//                    //}
//                    if (curX <= 910 && curX >= 630 && curY <= 740 && curY >= 680)                  // QUIT
//                    {
//                        result = al_show_native_message_box(display, game_title, "Warning",
//                                                            "Closing the game from the control tab can damage your data \nClose?",
//                                                            (const char *) ALLEGRO_MESSAGEBOX_YES_NO,
//                                                            0);
//                        if (result == 1)
//                            done = true;
//                        else
//                            done = false;
//                        main_menu = true;
//                        draw_main_menu = false;
//                        redraw = false;
//                        player_menu = false;
//                    }
//                }
//            }
//        }
//        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && player_menu ) {
//            if ( !main_menu ) {
//                al_draw_bitmap(player_menu_image, 0, 0, 0);
//                al_draw_filled_rounded_rectangle(650, 250, 890, 300, 10, 10, al_map_rgb(50, 150, 200));
//                al_draw_text(font, al_map_rgb(0, 0, 0), 680, 271, 0, "Number of Players :");
//                al_draw_filled_circle(630, 422, 50, al_map_rgb(67, 243, 255));
//                al_draw_text(font, al_map_rgb(0, 0, 0), 630, 422, ALLEGRO_ALIGN_CENTRE, "2");
//                al_draw_filled_circle(750, 422, 50, al_map_rgb(67, 243, 255));
//                al_draw_text(font, al_map_rgb(0, 0, 0), 750, 422, ALLEGRO_ALIGN_CENTRE, "3");
//                al_draw_filled_circle(870, 422, 50, al_map_rgb(67, 243, 255));
//                al_draw_text(font, al_map_rgb(0, 0, 0), 870, 422, ALLEGRO_ALIGN_CENTRE, "4");
//
//                al_flip_display();
//                if (event.mouse.button & 1 ) {
//                    if (curX >= 580 && curX <= 680 && curY >= 372 && curY <= 472)                // 2 Players
//                    {
//                        redraw = true;
//                        player_menu = false;
//                        //draw_player_menu = false;
//                        number_of_players = 2;
//                        player_soldiers_sum = 60;
//                        al_destroy_bitmap(player_menu_image);
//                        al_clear_to_color(al_map_rgb(0, 0, 0));
//                    }
//                    if (curX >= 700 && curX <= 800 && curY >= 372 && curY <= 472)           // 3 Players
//                    {
//                        redraw = true;
//                        player_menu = false;
//                        //draw_player_menu = false;
//                        number_of_players = 3;
//                        player_soldiers_sum = 75;
//                        al_destroy_bitmap(player_menu_image);
//                        al_clear_to_color(al_map_rgb(0, 0, 0));
//                    }
//                    if (curX >= 820 && curX <= 920 && curY >= 372 && curY <= 472)           // 4 Players
//                    {
//                        redraw = true;
//                        player_menu = false;
//                        //draw_player_menu = false;
//                        number_of_players = 4;
//                        player_soldiers_sum = 80;
//                        al_destroy_bitmap(player_menu_image);
//                        al_clear_to_color(al_map_rgb(0, 0, 0));
//                    }
//                }
//            }
//        }
//        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && pause_menu) {
//                al_draw_bitmap(pause_menu_image, 0, 0, 0);
//                al_flip_display();
//                if (event.mouse.button & 1) {
//                    if (curX <= 900 && curX >= 600 && curY <= 450 && curY >= 380)                  // Resume
//                    {
//                        pause_menu = false;
//                        redraw = true;
//                        done = false;
//                        al_destroy_bitmap(pause_menu_image);
//                        al_clear_to_color(al_map_rgb(0, 0, 0));
//                    }
//                    if (curX <= 900 && curX >= 600 && curY <= 570 && curY >= 515)                 // Save Game
//                    {
////                        pause_menu = true;
////                        al_destroy_bitmap(pause_menu_image);
////                        al_clear_to_color(al_map_rgb(0, 0, 0));
//                    }
//                    if (curX <= 900 && curX >= 600 && curY <= 690 && curY >= 635)                 // Main Menu
//                    {
//                        pause_menu = false;
//                        main_menu = false;
//                        redraw = false;
//                        done = false;
//                        al_destroy_bitmap(pause_menu_image);
//                        al_clear_to_color(al_map_rgb(0, 0, 0));
//                    }
//                }
//        }
//        if (event.type == ALLEGRO_EVENT_TIMER)                                // Frame rate per second
//        {
//            if (event.timer.source == timer)            // 60 fps
//            {
//                redraw = true;
////                pos_x += KEYS[RIGHT] * 25;
////                pos_x -= KEYS[LEFT] * 25;
//            }
//        }
//            if (turn_click) {
//                if (event.mouse.button & 1) {
//                    for (int i = 0; i < 7; ++i) {
//                        for (int j = 0; j < 6; ++j) {
//                            if (!(i >= 2 && i <= 4 && j == 1) && !(j >= 0 && j <= 1 && i == 6) &&
//                                !(j == 2 && i == 3) &&
//                                !(i == 6 && j == 3) &&
//                                !(i >= 4 && i <= 6 && j >= 4 && j <= 5)) {
//                                if (curX >= countries_Xaxe[j][i] && curX <= countries_Xaxe[j][i] + 200 &&
//                                    curY >= countries_Yaxe[j][i] && curY <= countries_Yaxe[j][i] + 100) {
//                                    player_soldiers[turn]--;
//                                    soldiers[k]++;
//                                    turn++;
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//            // If the user is in main menu
//            if (mainmenu && al_is_event_queue_empty(queue)) {
//                al_draw_bitmap(Risk_menu, 0, 0, 0);
//                al_flip_display();
//                redraw = false;
//                playermenu = false;
//                if (event.mouse.button & 1)              // If Left Button is clicked
//                {
//                    drawmenu = false;
//                    if (curX <= 910 && curX >= 630 && curY <= 510 && curY >= 450)                  // NEW Game
//                    {
//                        mainmenu = false;
//                        playermenu = true;
//                        done = false;
//                        al_destroy_bitmap(Risk_menu);
//                        al_clear_to_color(al_map_rgb(0, 0, 0));
//                    }
//                        //else if (curX <= 910 && curX >= 630 && curY <= 625 && curY >= 560);        // Load Game
//                        //{
//                        //  if (bazi save dare){
//                        //      load kon
//                        //  }
//                        //  else if (bazi save nadare)
//                        //  {
//                        //      peygham namayesh bede !
//                        //  }
//                        //}
//                    else if (curX <= 910 && curX >= 630 && curY <= 740 && curY >= 680)           // QUIT
//                    {
//                        result = al_show_native_message_box(display , game_title ,"Warning",
//                                                   "Closing the game from the control tab can damage your data \nClose?", NULL ,
//                                                   ALLEGRO_MESSAGEBOX_WARN | ALLEGRO_MESSAGEBOX_YES_NO );
//                        if (result == 1)
//                            done = true;
//                        mainmenu = false;
//                        playermenu = false;
//                    }
//                }
//            }
//        }
//        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && draw_player_menu)                     // Player Menu
//        {
//            //if the user is in player menu
//            if (player_menu ) {
//                al_draw_bitmap(player_menu_image, 0, 0, 0);
//                al_draw_filled_rounded_rectangle(650, 250, 890, 300, 10, 10, al_map_rgb(50, 150, 200));
//                al_draw_text(font, al_map_rgb(0, 0, 0), 680, 271, 0, "Number of Players :");
//                al_draw_filled_circle(630, 422, 50, al_map_rgb(67, 243, 255));
//                al_draw_text(font, al_map_rgb(0, 0, 0), 630, 422, ALLEGRO_ALIGN_CENTRE, "2");
//                al_draw_filled_circle(750, 422, 50, al_map_rgb(67, 243, 255));
//                al_draw_text(font, al_map_rgb(0, 0, 0), 750, 422, ALLEGRO_ALIGN_CENTRE, "3");
//                al_draw_filled_circle(870, 422, 50, al_map_rgb(67, 243, 255));
//                al_draw_text(font, al_map_rgb(0, 0, 0), 870, 422, ALLEGRO_ALIGN_CENTRE, "4");
//
//                al_flip_display();
//                redraw = false;
//                if (event.mouse.button & 1) {
//                    if (curX >= 580 && curX <= 680 && curY >= 372 && curY <= 472)                // 2 Players
//                    {
//                        player_menu = false;
//                        redraw = true;
//                        done = false;
//                        draw_player_menu = false;
//                        number_of_players = 2;
//                        player_soldiers_sum = 60;
//                        al_destroy_bitmap(player_menu_image);
//                        al_clear_to_color(al_map_rgb(0, 0, 0));
//                    }
//                    else if (curX >= 700 && curX <= 800 && curY >= 372 && curY <= 472)           // 3 Players
//                    {
//                        player_menu = false;
//                        redraw = true;
//                        done = false;
//                        draw_player_menu = false;
//                        number_of_players = 3;
//                        player_soldiers_sum = 75;
//                        al_destroy_bitmap(player_menu_image);
//                        al_clear_to_color(al_map_rgb(0, 0, 0));
//                    }
//                    else if (curX >= 820 && curX <= 920 && curY >= 372 && curY <= 472)           // 4 Players
//                    {
//                        player_menu = false;
//                        redraw = true;
//                        done = false;
//                        draw_player_menu = false;
//                        number_of_players = 4;
//                        player_soldiers_sum = 80;
//                        al_destroy_bitmap(player_menu_image);
//                        al_clear_to_color(al_map_rgb(0, 0, 0));
//                    }
//                }
//            }
//        }
//        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && turn_click && !player_menu && !main_menu && redraw)
//        {
//            if (event.mouse.button &1)
//            {
//                for (int i = 0; i < 7; ++i) {
//                    for (int j = 0; j < 6; ++j) {
//                        if (!(i >= 2 && i <= 4 && j == 1) && !(j >= 0 && j <= 1 && i == 6) &&
//                            !(j == 2 && i == 3) &&
//                            !(i == 6 && j == 3) &&
//                            !(i >= 4 && i <= 6 && j >= 4 && j <= 5)) {
//                            if (curX >= countries_Xaxe[j][i] && curX <= countries_Xaxe[j][i] + 200 &&
//                                curY >= countries_Yaxe[j][i] && curY <= countries_Yaxe[j][i] + 100) {
//                                player_soldiers[turn]--;
//                                soldiers[k]++;
//                                turn++;
//                            }
//                        }
//                    }
//                }
//            }
//        }
/////////////////chert music
//        if (event.type == ALLEGRO_EVENT_KEY_DOWN)
//            if (event.keyboard.keycode == ALLEGRO_KEY_P)
//                al_play_audio(background_music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

/////////////////////////////////////////////////Game Logic !
//        if ( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && redraw ) {
//            if (al_is_event_queue_empty(map_queue) && !main_menu && player_menu) {
//                redraw = false;
//                al_draw_filled_rectangle(0, 0, 1500, 844, al_map_rgb(53, 212, 255));  //background
//                al_draw_bitmap(background_sea, 0, 0, 0);              // The Sea
//                //taghsim sarbaz va keshvar
//                while (j != number_of_players) {
//                    player_contries[j] = number_of_countries / number_of_players;
//                    player_soldiers[j] = player_soldiers_sum / number_of_players;
//                    if (number_of_countries % number_of_players != 0) {
//                        player_contries[j]++;
//                        number_of_countries--;
//                    }
//                    j++;
//                }
//                //sarbaz dehi random
//                for (int i = 0; i < 29; ++i) {
//                    if (number_of_players == 2)
//                        countries[i] = rand() % 2;
//                    else if (number_of_players == 3)
//                        countries[i] = rand() % 3;
//                    else if (number_of_players == 4)
//                        countries[i] = rand() % 4;
//                    soldiers[i] = 1;
//                }
//                //keshvar male har bazikon
//                for (int i = 0; i < 7; ++i) {
//                    for (int j = 0; j < 6; ++j) {
//                        if (!(i >= 2 && i <= 4 && j == 1) && !(j >= 0 && j <= 1 && i == 6) && !(j == 2 && i == 3) &&
//                            !(i == 6 && j == 3) &&
//                            !(i >= 4 && i <= 6 && j >= 4 && j <= 5)) {
//                            //al_draw_filled_circle(j * 200 + 100, i * 100 + 50, 20, al_map_rgb(255, 255, 255));
//                            al_draw_rectangle(j * 200, i * 100, (j + 1) * 200, (i + 1) * 100, al_map_rgb(0, 0, 0), 1);
//                            if (countries[k] == 0) {
//                                al_draw_filled_rectangle(j * 200, i * 100, (j + 1) * 200, (i + 1) * 100,
//                                                         al_map_rgb(255, 0, 0));
//                                al_draw_textf(font, al_map_rgb(0, 0, 0), j * 200 + 100, i * 100 + 50, 0, "%i",
//                                              soldiers[k]);
//                                countries_Xaxe[j][i] = j * 200;
//                                countries_Yaxe[j][i] = i * 100;
//                            }
//                            if (countries[k] == 1) {
//                                al_draw_filled_rectangle(j * 200, i * 100, (j + 1) * 200, (i + 1) * 100,
//                                                         al_map_rgb(0, 100, 255));
//                                al_draw_textf(font, al_map_rgb(0, 0, 0), j * 200 + 100, i * 100 + 50, 0, "%i",
//                                              soldiers[k]);
//                                countries_Xaxe[j][i] = j * 200;
//                                countries_Yaxe[j][i] = i * 100;
//                            }
//                            if (countries[k] == 2) {
//                                al_draw_filled_rectangle(j * 200, i * 100, (j + 1) * 200, (i + 1) * 100,
//                                                         al_map_rgb(255, 255, 0));
//                                al_draw_textf(font, al_map_rgb(0, 0, 0), j * 200 + 100, i * 100 + 50, 0, "%i",
//                                              soldiers[k]);
//                                countries_Xaxe[j][i] = j * 200;
//                                countries_Yaxe[j][i] = i * 100;
//                            }
//                            if (countries[k] == 3) {
//                                al_draw_filled_rectangle(j * 200, i * 100, (j + 1) * 200, (i + 1) * 100,
//                                                         al_map_rgb(0, 255, 100));
//                                al_draw_textf(font, al_map_rgb(0, 0, 0), j * 200 + 100, i * 100 + 50, 0, "%i",
//                                              soldiers[k]);
//                                countries_Xaxe[j][i] = j * 200;
//                                countries_Yaxe[j][i] = i * 100;
//                            }
//                            k++;
//                        }
//                    }
//                }
//                //sarbazdehi avaliye
//                for (turn = 0; turn < number_of_players; ++turn) {
//                    for (int i = 0; i <= number_of_countries + 1; ++i) {
//                        if (countries[i] == turn)
//                            player_soldiers[turn]--;
//                    }
//                }
//                turn = 0;
//                while (all_players_zero != number_of_players) {
//                    ///age keshvar khudeshu click kard
//                    if (turn == countries[k])
//                        turn_click = true;
//                    //The Zard
//                    print_turn_box(turn);
//                    //begrad bebin hame bazikona sarbaz darn ?
//                    for (int i = 0; i < player_soldiers[turn - 1]; ++i) {
//                        if (player_soldiers[i] == 0)
//                            all_players_zero++;
//                    }
//                    k++;
//                }
//                if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && turn_click && !player_menu && !main_menu &&
//                    redraw) {
//                    if (event.mouse.button & 1) {
//                        for (int i = 0; i < 7; ++i) {
//                            for (int j = 0; j < 6; ++j) {
//                                if (!(i >= 2 && i <= 4 && j == 1) && !(j >= 0 && j <= 1 && i == 6) &&
//                                    !(j == 2 && i == 3) &&
//                                    !(i == 6 && j == 3) &&
//                                    !(i >= 4 && i <= 6 && j >= 4 && j <= 5)) {
//                                    if (curX >= countries_Xaxe[j][i] && curX <= countries_Xaxe[j][i] + 200 &&
//                                        curY >= countries_Yaxe[j][i] && curY <= countries_Yaxe[j][i] + 100) {
//                                        player_soldiers[turn]--;
//                                        soldiers[k]++;
//                                        turn++;
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//                draw_black_borders();
//                // state of game
//                al_draw_filled_triangle(800, 740, 840, 770, 800, 800, al_map_rgb(255, 255, 255));
//                //buttun next
//                if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
//                    if (event.mouse.button & 1) {
//                        if (840 >= curX && curX >= 800 && curY <= 790 && curY >= 750) {
//                            pos_x += 130;
//                        }
//                    }
//                }
//                if (pos_x < 535)
//                    state_box(pos_x, pos_y, 'R');
//                if (pos_x < 665 && pos_x >= 535)
//                    state_box(pos_x, pos_y, 'A');
//                if (pos_x < 795 && pos_x >= 665)
//                    state_box(pos_x, pos_y, 'F');
//                if (pos_x >= 795)
//                    pos_x = 405;
//                //state of players
//                for (int i = 0; i < number_of_players; i++) {
//                    al_draw_filled_rounded_rectangle(1250, i * 170 + 100, 1470, i * 170 + 230, 15, 15,
//                                                     al_map_rgb(250, 128, 114));              //soratiye
//                    al_draw_bitmap(soldier_image, 1255, i * 170 + 135, 0);
//                    al_draw_bitmap(score_image, 1255, i * 170 + 175, 0);
//                    //chape profile
//                    if (i == 0)
//                        al_draw_filled_circle(1415, i * 170 + 155, 35, al_map_rgb(255, 0, 0));
//                    if (i == 1)
//                        al_draw_filled_circle(1415, i * 170 + 155, 35, al_map_rgb(0, 100, 255));
//                    if (i == 2)
//                        al_draw_filled_circle(1415, i * 170 + 155, 35, al_map_rgb(255, 255, 0));
//                    if (i == 3)
//                        al_draw_filled_circle(1415, i * 170 + 155, 35, al_map_rgb(0, 255, 100));
//                    al_draw_textf(font, al_map_rgb(0, 0, 0), 1260, i * 170 + 120, ALLEGRO_ALIGN_LEFT, "Player %i",
//                                  i + 1);
//                    al_draw_textf(font, al_map_rgb(255, 255, 255), 1300, i * 170 + 150, ALLEGRO_ALIGN_LEFT, "%i",
//                                  player_soldiers[i]);
//                }
//                al_flip_display();
//            }