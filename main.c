#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <display.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>

#define game_title  "Risk Game Quit"
#define game_width  1500
#define game_height  844
#define main_menu 1
#define player_menu 2
#define map 3
#define pause_menu 4
#define help_menu 5
#define help_menu1 51
#define help_menu2 52
#define help_menu3 53
#define help_menu4 54
#define Info_menu 6
#define Winner_page 7
#define THESEA 10
#define receive 0
#define attack 1
#define fortify 2

//Prototypes
void sort(int array[], int size);

int defender_battle(int array_defender[], int size1, int array_attacker[], int defender);

int attacker_battle(int array_defender[], int size1, int array_attacker[], int attacker);

void draw_black_borders();

//void state_box(int pos_x, int pos_y, char state);

//void print_turn_box(int turn);

int main() {
    al_init();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(3);
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_native_dialog_addon();

    //primitive variables
    int result;
    int floor_num;
    int dor = 0;
    int page_switch = main_menu;
    int help_menu_switch;
    int i = 0, j = 0, k = 0, r = 0;
    int number_of_players;
    int player_soldiers_sum;
    int number_of_countries = 29;
    int player_soldiers[4] = {0};
    int player_contries[4] = {0};
    int players_zero_counter[4] = {1, 1, 1, 1};
    int countries[7][6]; //har keshvar male kodoom bazikone
    int fortify_countries[9][8];
    int soldiers[7][6]; //tedad sarbazayi ke too har keshvaran
    int turn = 0;
    int player_turn = 0;
    int game_state = receive;
    int attacker = 0;
    int defender = 0;
    int array_attacker[3] = {0};
    int array_defender[2] = {0};
    int x = 6576, y = 7328, m = 6655, l = 7456;
    int battle_switch;
    int winner = 10;
    int Hist[400][2];
    int player_continent_conquer[4][5] = {{0, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 0}};
    bool redraw = false;
    bool turn_click = false;
    bool random_dehi = true;
    bool done = false;
    bool first_soldier_conscription = true;
    bool taghsim_sarbaz_keshvar = true;
    bool receive_ending = false;
    bool attack_forever = false;
    bool receive_forever = true;
    bool fortify_forever = false;
    bool turn_receive = true;
    bool origin = true;
    bool destination = false;
    bool circle_draw1 = true;
    bool circle_draw2 = true;
    bool w = true;
    bool s = true;

    //60 frames per second OR 1/60 th second
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_SAMPLE *warfare_sound = al_load_sample("../warfare_gunshots_semi_automatic_distant.opus");
    ALLEGRO_SAMPLE *winner_music = al_load_sample("../winner_music.opus");
    ALLEGRO_FONT *font2 = al_load_ttf_font("../comic.ttf", 18, 0);

    ALLEGRO_AUDIO_STREAM *background_music = al_load_audio_stream("../backgroundmusic.opus", 2, 2048);
    al_set_audio_stream_playmode(background_music, ALLEGRO_PLAYMODE_LOOP);
    al_attach_audio_stream_to_mixer(background_music, al_get_default_mixer());

    ALLEGRO_DISPLAY *display = al_create_display(game_width, game_height);                    //display
    ALLEGRO_BITMAP *Risk_menu = al_load_bitmap("../Risk_menu.jpg");                        //main menu
    ALLEGRO_BITMAP *background_sea = al_load_bitmap("../background-sea-water.jpg");      //background sea
    ALLEGRO_BITMAP *soldier_image = al_load_bitmap("../soldier.png");                   //soldier image
    ALLEGRO_BITMAP *dota_logo = al_load_bitmap("../dota_logo.jpg");                      //dota logo image
    ALLEGRO_BITMAP *Risk_pause_menu = al_load_bitmap("../Risk_pause_menu.jpg");        //pause menu image
    ALLEGRO_BITMAP *Risk_player_menu = al_load_bitmap("../Risk_player_menu.jpg");      //player menu image
    ALLEGRO_BITMAP *Help_menu1 = al_load_bitmap("../Help_menu1.jpg");
    ALLEGRO_BITMAP *Help_menu2 = al_load_bitmap("../Help_menu2.jpg");
    ALLEGRO_BITMAP *Help_menu3 = al_load_bitmap("../Help_menu3.jpg");
    ALLEGRO_BITMAP *Help_menu4 = al_load_bitmap("../Help_menu4.jpg");
    ALLEGRO_BITMAP *info_menu = al_load_bitmap("../info_menu.jpg");
    ALLEGRO_BITMAP *map_background = al_load_bitmap("../map_background.jpg");
    ALLEGRO_BITMAP *profile_abi = al_load_bitmap("../Abi.jpg");
    ALLEGRO_BITMAP *profile_banafsh = al_load_bitmap("../banafsh.jpg");
    ALLEGRO_BITMAP *profile_sabz = al_load_bitmap("../sabz.jpg");
    ALLEGRO_BITMAP *profile_ghermez = al_load_bitmap("../ghermez.jpg");
    ALLEGRO_BITMAP *winner_page1 = al_load_bitmap("../winner_page/winner_page1.jpg");
    ALLEGRO_BITMAP *winner_page2 = al_load_bitmap("../winner_page/winner_page2.jpg");
    ALLEGRO_BITMAP *winner_page3 = al_load_bitmap("../winner_page/winner_page3.jpg");
    ALLEGRO_BITMAP *winner_page4 = al_load_bitmap("../winner_page/winner_page4.jpg");
    //a struct for getting the state of mouse everywhere you want
    ALLEGRO_MOUSE_STATE statemouse;

    //These three lines make circles smoother
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    //now it's time to register our objects
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));

    ALLEGRO_EVENT event;
    al_start_timer(timer);
    srand(time(0));

    // all of Hist array Blocks should be zero
    for (int n = 0; n < 400; ++n) {
        for (int p = 0; p < 2; ++p) {
            Hist[n][p] = 0;
        }
    }
    // around fortify_countries array should be the value 10
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 8; j++) {
            fortify_countries[i][j] = 10;
        }
    }
    ///////////////////////////////////////////////////********* Game Loop ! *********//////////////////////////////////////////////////////////////
    while (!done) {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }
        if (done)
            break;
        //Escape key
        if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            done = true;
        }
        // The most if of the game !
        if (redraw && al_is_event_queue_empty(queue)) {
            redraw = false;
            switch (page_switch) {
                case main_menu:
                    al_draw_bitmap(Risk_menu, 0, 0, 0);
                    al_get_mouse_state(&statemouse);
                    if (al_mouse_button_down(&statemouse, 1)) {
                        if (statemouse.x <= 910 && statemouse.x >= 630 && statemouse.y <= 510 &&
                            statemouse.y >= 450) {                   // NEW Game
                            page_switch = player_menu;
                        }
                        //if (curX <= 910 && curX >= 630 && curY <= 625 && curY >= 560)            // Load Game
                        //{
                        //  if (bazi save dare){
                        //      load kon
                        //  }
                        //  else if (bazi save nadare)
                        //  {
                        //      peygham namayesh bede !
                        //  }
                        //}
                        if (statemouse.x <= 910 && statemouse.x >= 630 && statemouse.y <= 740 &&
                            statemouse.y >= 680) {                  // QUIT
                            result = al_show_native_message_box(display, game_title, "Warning",
                                                                "Closing the game from the control tab can damage your data \nClose?",
                                                                0,
                                                                ALLEGRO_MESSAGEBOX_WARN | ALLEGRO_MESSAGEBOX_YES_NO);
                            if (result == 1)
                                done = true;
                            else
                                done = false;
                        }
                        al_rest(0.3);
                    }
                    break;
                case player_menu:
                    al_draw_bitmap(Risk_player_menu, 0, 0, 0);
                    al_get_mouse_state(&statemouse);
                    if (al_mouse_button_down(&statemouse, 1)) {
                        if (statemouse.x >= 640 && statemouse.x <= 940 && statemouse.y >= 300 &&
                            statemouse.y <= 360)            // 2 Players
                        {
                            page_switch = map;
                            number_of_players = 2;
                            player_soldiers_sum = 60;
                        }
                        if (statemouse.x >= 640 && statemouse.x <= 940 && statemouse.y >= 420 &&
                            statemouse.y <= 480)           // 3 Players
                        {
                            page_switch = map;
                            number_of_players = 3;
                            player_soldiers_sum = 75;
                        }
                        if (statemouse.x >= 640 && statemouse.x <= 940 && statemouse.y >= 540 &&
                            statemouse.y <= 590)           // 4 Players
                        {
                            page_switch = map;
                            number_of_players = 4;
                            player_soldiers_sum = 80;
                        }
                        al_rest(0.1);
                    }
                    break;
                case map:
                    al_draw_bitmap(map_background, 0, 0, 0);                   //Background
                    al_draw_bitmap(background_sea, 0, 0, 0);                   //The Sea
                    al_draw_bitmap(dota_logo, 1440, 780, 0);                   //Dota Logo
                    //taghsim sarbaz va keshvar
                    if (taghsim_sarbaz_keshvar) {
                        taghsim_sarbaz_keshvar = false;
                        j = 0;
                        while (j != number_of_players) {
                            player_contries[j] = number_of_countries / number_of_players;
                            player_soldiers[j] = player_soldiers_sum / number_of_players;
                            if (number_of_countries % number_of_players != 0) {
                                player_contries[j]++;
                                number_of_countries--;
                            }
                            j++;
                        }
                        number_of_countries = 29;
                    }
                    //keshvar dehi random
                    //////////////////////////////////////////
//                    for (int n = 0; n < 7; ++n) {
//                        for (int i1 = 0; i1 < 6; ++i1) {
//                            if (!(i >= 2 && i <= 4 && j == 1) && !(j >= 0 && j <= 1 && i == 6) &&
//                                                                    !(j == 2 && i == 3) &&
//                                                                    !(i == 6 && j == 3) &&
//                                                                    !(i >= 4 && i <= 6 && j >= 4 && j <= 5)) {
//                                countries[i][j] = 0;
//                            } else
//                                countries[i][j] = THESEA;
//                        }
//                    }
                    ////////////////////////////////////////////
                    if (random_dehi) {
                        random_dehi = false;
                        for (i = 0; i < 7; i++) {
                            for (j = 0; j < 6; j++) {
                                //if there where no sea
                                if (!(i >= 2 && i <= 4 && j == 1) && !(j >= 0 && j <= 1 && i == 6) &&
                                    !(j == 2 && i == 3) &&
                                    !(i == 6 && j == 3) &&
                                    !(i >= 4 && i <= 6 && j >= 4 && j <= 5)) {
                                    player_turn = turn % number_of_players;
                                    switch (number_of_players) {
                                        case 2:
                                        RAND2 :
                                            if (player_contries[0] != 0 || player_contries[1] != 0) {
                                                countries[i][j] = rand() % 3;
                                                if (player_contries[countries[i][j]] == 0)
                                                    goto RAND2;
                                                else {
                                                    player_contries[countries[i][j]]--;
                                                    turn++;
                                                }
                                            }
                                            break;
                                        case 3:
                                        RAND3 :
                                            if (player_contries[0] != 0 || player_contries[1] != 0 ||
                                                player_contries[2] != 0) {
                                                countries[i][j] = rand() % 3;
                                                if (player_contries[countries[i][j]] == 0)
                                                    goto RAND3;
                                                else {
                                                    player_contries[countries[i][j]]--;
                                                    turn++;
                                                }
                                            }
                                            break;
                                        case 4:
                                        RAND4 :
                                            if (player_contries[0] != 0 || player_contries[1] != 0 ||
                                                player_contries[2] != 0 || player_contries[3] != 0) {
                                                countries[i][j] = rand() % 4;
                                                if (player_contries[countries[i][j]] == 0)
                                                    goto RAND4;
                                                else {
                                                    player_contries[countries[i][j]]--;
                                                    turn++;
                                                }
                                            }
                                            break;
                                    }
                                    soldiers[i][j] = 1;
                                } else
                                    countries[i][j] = THESEA;
                            }
                        }
                    }
                    //rang dehi avaliye
                    for (i = 0; i < 7; i++) {
                        for (j = 0; j < 6; j++) {
                            if (countries[i][j] == 0) {
                                al_draw_filled_rectangle(j * 200, i * 100, (j + 1) * 200, (i + 1) * 100,
                                                         al_map_rgb(200, 50, 0));
                                al_draw_textf(font2, al_map_rgb(0, 0, 0), j * 200 + 90, i * 100 + 40, 0,
                                              "%i", soldiers[i][j]);
                            }
                            if (countries[i][j] == 1) {
                                al_draw_filled_rectangle(j * 200, i * 100, (j + 1) * 200, (i + 1) * 100,
                                                         al_map_rgb(0, 200, 255));
                                al_draw_textf(font2, al_map_rgb(0, 0, 0), j * 200 + 90, i * 100 + 40, 0,
                                              "%i", soldiers[i][j]);
                            }
                            if (countries[i][j] == 2) {
                                al_draw_filled_rectangle(j * 200, i * 100, (j + 1) * 200, (i + 1) * 100,
                                                         al_map_rgb(150, 0, 150));
                                al_draw_textf(font2, al_map_rgb(0, 0, 0), j * 200 + 90, i * 100 + 40, 0,
                                              "%i", soldiers[i][j]);
                            }
                            if (countries[i][j] == 3) {
                                al_draw_filled_rectangle(j * 200, i * 100, (j + 1) * 200, (i + 1) * 100,
                                                         al_map_rgb(0, 150, 50));
                                al_draw_textf(font2, al_map_rgb(0, 0, 0), j * 200 + 90, i * 100 + 40, 0,
                                              "%i", soldiers[i][j]);
                            }
                        }
                    }
                    //the black borders
                    draw_black_borders();
                    //sarbaz dehi avaliye
                    if (first_soldier_conscription) {
                        first_soldier_conscription = false;
                        for (turn = 0; turn < number_of_players; turn++) {
                            for (i = 0; i < 7; i++) {
                                for (j = 0; j < 6; j++) {
                                    if (countries[i][j] == turn)
                                        player_soldiers[turn]--;
                                }
                            }
                        }
                        turn = 0;
                    }
                    //sarbaz dehi asli
                    if (receive_forever) {
                        al_get_mouse_state(&statemouse);
                        if (al_mouse_button_down(&statemouse, 1)) {
                            for (i = 0; i < 7; i++) {
                                for (j = 0; j < 6; j++) {
                                    if (statemouse.x >= 200 * j && statemouse.x <= 200 * (j + 1) &&
                                        statemouse.y >= 100 * i && statemouse.y <= 100 * (i + 1)) {
                                        player_turn = turn % number_of_players;
                                        if (player_soldiers[player_turn] == 0)
                                            players_zero_counter[player_turn] = 0;
                                        if (players_zero_counter[player_turn] != 0 &&
                                            player_soldiers[player_turn] > 0) {
                                            if (player_turn == countries[i][j])
                                                turn_click = true;
                                            //age keshvar khudesho click kard
                                            if (turn_click) {
                                                turn_click = false;
                                                soldiers[i][j]++;
                                                player_soldiers[player_turn]--;
                                                turn++;
                                            }
                                        } else
                                            turn++;
                                    }
                                    //Sharte Attack
                                    switch (number_of_players) {
                                        case 2:
                                            if (player_soldiers[0] == 0 && player_soldiers[1] == 0) {
                                                game_state = attack;
                                                receive_forever = false;
                                                attack_forever = true;
                                                turn = 0;
                                            }
                                            break;
                                        case 3:
                                            if (player_soldiers[0] == 0 && player_soldiers[1] == 0 &&
                                                player_soldiers[2] == 0) {
                                                game_state = attack;
                                                receive_forever = false;
                                                attack_forever = true;
                                                turn = 0;
                                            }
                                            break;
                                        case 4:
                                            if (player_soldiers[0] == 0 && player_soldiers[1] == 0 &&
                                                player_soldiers[2] == 0 && player_soldiers[3] == 0) {
                                                game_state = attack;
                                                receive_forever = false;
                                                attack_forever = true;
                                                turn = 0;
                                            }
                                            break;
                                    }
                                }
                            }
                            al_rest(0.1);
                        }
                    }
                    //Mostatile Zard
                    player_turn = turn % number_of_players;
                    switch (player_turn) {
                        case 0:
                            al_draw_filled_rounded_rectangle(1235, 85, 1485, 215, 15, 15, al_map_rgb(255, 255, 0));
                            break;
                        case 1:
                            al_draw_filled_rounded_rectangle(1235, 245, 1485, 375, 15, 15, al_map_rgb(255, 255, 0));
                            break;
                        case 2:
                            al_draw_filled_rounded_rectangle(1235, 405, 1485, 535, 15, 15, al_map_rgb(255, 255, 0));
                            break;
                        case 3:
                            al_draw_filled_rounded_rectangle(1235, 565, 1485, 695, 15, 15, al_map_rgb(255, 255, 0));
                            break;
                    }
                    //Purple rectangle
                    al_draw_filled_rounded_rectangle(400, 740, 800, 800, 8, 8, al_map_rgb(175, 19, 114));
                    switch (game_state % 3) {
                        case receive:
                            al_draw_text(font2, al_map_rgb(255, 255, 255), 580, 750, 0, "Receive");
                            al_draw_filled_rectangle(405, 790, 535, 800, al_map_rgb(244, 74, 250));
                            break;
                        case attack:
                            al_draw_text(font2, al_map_rgb(255, 255, 255), 580, 750, 0, "Attack");
                            al_draw_filled_rectangle(535, 790, 665, 800, al_map_rgb(244, 74, 250));
                            break;
                        case fortify:
                            al_draw_text(font2, al_map_rgb(255, 255, 255), 580, 750, 0, "Fortify");
                            al_draw_filled_rectangle(665, 790, 795, 800, al_map_rgb(244, 74, 250));
                            break;
                    }
                    //White triangle
                    al_draw_filled_triangle(800, 740, 840, 770, 800, 800, al_map_rgb(255, 255, 255));
                    //Click triangle
                    al_get_mouse_state(&statemouse);
                    if (al_mouse_button_down(&statemouse, 1)) {
                        if (statemouse.x >= 800 && statemouse.x <= 840 && statemouse.y >= 740 && statemouse.y <= 800) {
                            switch (game_state % 3) {
                                case receive:
                                    result = al_show_native_message_box(display, "Change turn", "Access Denied ",
                                                                        " ",
                                                                        0,
                                                                        ALLEGRO_MESSAGEBOX_WARN);
                                    if (result == 1) {
                                        result = 5;
                                        receive_forever = true;
                                        attack_forever = false;
                                        fortify_forever = false;
                                        game_state = receive;
                                    } else {
                                        result = 5;
                                        receive_forever = true;
                                        attack_forever = false;
                                        fortify_forever = false;
                                        game_state = receive;
                                    }
                                    break;
                                case attack:
                                    game_state++;
                                    attack_forever = false;
                                    fortify_forever = true;
                                    receive_forever = false;
                                    break;
                                case fortify:
                                    result = al_show_native_message_box(display, "Change turn", " ",
                                                                        "Are you sure to change turn ?",
                                                                        0,
                                                                        ALLEGRO_MESSAGEBOX_YES_NO);
                                    if (result == 1) {
                                        result = 5;
                                        receive_forever = false;
                                        attack_forever = true;
                                        fortify_forever = false;
                                        game_state = attack;
                                        dor++;
                                        turn++;
                                    } else {
                                        result = 5;
                                        game_state = fortify;
                                        fortify_forever = true;
                                        attack_forever = false;
                                        receive_forever = false;
                                    }
                                    break;
                            }
                        }
                        al_rest(0.3);
                    }
                    //Pink rectangle
                    for (i = 0; i < number_of_players; i++) {
                        al_draw_filled_rounded_rectangle(1250, i * 160 + 100, 1470, i * 160 + 200, 15, 15,
                                                         al_map_rgb(250, 128, 114));
                        al_draw_bitmap(soldier_image, 1255, i * 160 + 145, 0);
                        al_draw_textf(font2, al_map_rgb(0, 0, 0), 1260, i * 160 + 110, ALLEGRO_ALIGN_LEFT,
                                      "Player %i", i + 1);
                        al_draw_textf(font2, al_map_rgb(255, 255, 255), 1300, i * 160 + 150, ALLEGRO_ALIGN_LEFT,
                                      "%i", player_soldiers[i]);
                        //Profile
                        if (i == 0)
                            al_draw_bitmap(profile_ghermez, 1390, i * 160 + 115, 0);
                        if (i == 1)
                            al_draw_bitmap(profile_abi, 1390, i * 160 + 115, 0);
                        if (i == 2)
                            al_draw_bitmap(profile_banafsh, 1390, i * 160 + 115, 0);
                        if (i == 3)
                            al_draw_bitmap(profile_sabz, 1390, i * 160 + 115, 0);
                    }
                    //Attack
                    if (attack_forever) {
                        receive_forever = false;
                        if (!w) {
                            w = true;
                            y = 7328;
                            x = 6345;
                        }
                        //The Mohajem (White circle)
                        al_get_mouse_state(&statemouse);
                        if (al_mouse_button_down(&statemouse, 1)) {
                            for (i = 0; i < 7; i++) {
                                for (j = 0; j < 6; j++) {
                                    if (statemouse.x >= 200 * j && statemouse.x <= 200 * (j + 1) &&
                                        statemouse.y >= 100 * i && statemouse.y <= 100 * (i + 1)) {
                                        if (player_turn == countries[i][j]) {
                                            turn_click = true;
                                            y = i;
                                            x = j;
                                        }
                                    }
                                }
                            }
                            al_rest(0.3);
                        }
                        al_draw_circle(200 * x + 100, 100 * y + 50, 40, al_map_rgb(255, 255, 255),
                                       5);
                        //Modafe (Black circle)
                        if (turn_click) {
                            ////////////////////////////////////////////////////////////////////////////////////UP
                            if (countries[y - 1][x] != THESEA && y - 1 >= 0 &&
                                countries[y - 1][x] != countries[y][x]) {
                                if (al_mouse_button_down(&statemouse, 1)) {
                                    if (statemouse.x >= 200 * x && statemouse.x <= 200 * (x + 1) &&
                                        statemouse.y >= 100 * (y - 1) && statemouse.y <= 100 * y) {
                                        //تعیین تعداد سرباز های مدافع
                                        if (soldiers[y - 1][x] >= 2) {
                                            defender = 2;
                                            soldiers[y - 1][x] -= defender;
                                        } else {
                                            defender = 1;
                                            soldiers[y - 1][x] = 0;
                                        }
                                        //تعیین تعداد سرباز های مهاجم
                                        if (soldiers[y][x] >= 4) {
                                            attacker = 3;
                                            soldiers[y][x] -= attacker;
                                        } else if (soldiers[y][x] != 1) {
                                            attacker = soldiers[y][x] - 1;
                                            soldiers[y][x] -= attacker;
                                        } else if (soldiers[y][x] == 1) {
                                            attacker = 0;
                                        }
                                        //رندوم ریزی
                                        for (i = 0; i < 2; ++i) {
                                            array_defender[i] = rand() % 6;
                                        }
                                        for (i = 0; i < 3; ++i) {
                                            array_attacker[i] = rand() % 6;
                                        }
                                        sort(array_defender, 2);
                                        sort(array_attacker, 3);
                                        if ((defender == 1 && attacker != 0) || (defender == 2 && attacker == 1)) {
                                            attacker = attacker_battle(array_defender, 1, array_attacker, attacker
                                            );
                                            defender = defender_battle(array_defender, 1, array_attacker, defender
                                            );
                                        } else if (defender == 2 && attacker != 0) {
                                            attacker = attacker_battle(array_defender, 2, array_attacker, attacker
                                            );
                                            defender = defender_battle(array_defender, 2, array_attacker, defender
                                            );
                                        }
                                        //Enteghal sarbaz
                                        if (defender == 0 && soldiers[y - 1][x] == 0) {
                                            player_contries[countries[y - 1][x]]--;
                                            player_contries[countries[y][x]]++;
                                            soldiers[y - 1][x] = attacker;
                                            countries[y - 1][x] = countries[y][x];
                                        }
                                            //bargasht sarbaz
                                        else {
                                            soldiers[y][x] += attacker;
                                            soldiers[y - 1][x] += defender;
                                        }
                                    }
                                    al_rest(0.3);
                                    al_play_sample(warfare_sound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                                }
                                al_draw_circle(200 * x + 100, 100 * (y - 1) + 50, 40, al_map_rgb(0, 0, 0), 5);
                            }
                            ////////////////////////////////////////////////////////////////////////////////////DOWN
                            if (countries[y + 1][x] != THESEA && y + 1 < 7 &&
                                countries[y + 1][x] != countries[y][x]) {
                                if (al_mouse_button_down(&statemouse, 1)) {
                                    if (statemouse.x >= 200 * x && statemouse.x <= 200 * (x + 1) &&
                                        statemouse.y >= 100 * (y + 1) && statemouse.y <= 100 * (y + 2)) {
                                        //تعیین تعداد سرباز های مدافع
                                        if (soldiers[y + 1][x] >= 2) {
                                            defender = 2;
                                            soldiers[y + 1][x] -= defender;
                                        } else {
                                            defender = 1;
                                            soldiers[y + 1][x] = 0;
                                        }
                                        //تعیین تعداد سرباز های مهاجم
                                        if (soldiers[y][x] >= 4) {
                                            attacker = 3;
                                            soldiers[y][x] -= attacker;
                                        } else if (soldiers[y][x] != 1) {
                                            attacker = soldiers[y][x] - 1;
                                            soldiers[y][x] -= attacker;
                                        } else if (soldiers[y][x] == 1) {
                                            attacker = 0;
                                        }
                                        //رندوم ریزی
                                        for (i = 0; i < 2; ++i) {
                                            array_defender[i] = rand() % 6;
                                        }
                                        for (i = 0; i < 3; ++i) {
                                            array_attacker[i] = rand() % 6;
                                        }
                                        sort(array_defender, 2);
                                        sort(array_attacker, 3);
                                        if ((defender == 1 && attacker != 0) || (defender == 2 && attacker == 1)) {
                                            attacker = attacker_battle(array_defender, 1, array_attacker, attacker
                                            );
                                            defender = defender_battle(array_defender, 1, array_attacker, defender
                                            );
                                        } else if (defender == 2 && attacker != 0) {
                                            attacker = attacker_battle(array_defender, 2, array_attacker, attacker
                                            );
                                            defender = defender_battle(array_defender, 2, array_attacker, defender
                                            );
                                        }
                                        //The Hejrat
                                        if (defender == 0 && soldiers[y + 1][x] == 0) {
                                            player_contries[countries[y + 1][x]]--;
                                            player_contries[countries[y][x]]++;
                                            soldiers[y + 1][x] = attacker;
                                            countries[y + 1][x] = countries[y][x];
                                        }
                                            //The Bargasht
                                        else {
                                            soldiers[y][x] += attacker;
                                            soldiers[y + 1][x] += defender;
                                        }
                                        al_rest(0.3);
                                        al_play_sample(warfare_sound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                                    }
                                }
                                al_draw_circle(200 * x + 100, 100 * (y + 1) + 50, 40, al_map_rgb(0, 0, 0), 5);
                            }
                            ///////////////////////////////////////////////////////////////////////////////////RIGHT
                            if (countries[y][x + 1] != THESEA && x + 1 < 6 &&
                                countries[y][x + 1] != countries[y][x]) {
                                if (al_mouse_button_down(&statemouse, 1)) {
                                    if (statemouse.x >= 200 * (x + 1) && statemouse.x <= 200 * (x + 2) &&
                                        statemouse.y >= 100 * y && statemouse.y <= 100 * (y + 1)) {
                                        //تعیین تعداد سرباز های مدافع
                                        if (soldiers[y][x + 1] >= 2) {
                                            defender = 2;
                                            soldiers[y][x + 1] -= defender;
                                        } else {
                                            defender = 1;
                                            soldiers[y][x + 1] = 0;
                                        }
                                        //تعیین تعداد سرباز های مهاجم
                                        if (soldiers[y][x] >= 4) {
                                            attacker = 3;
                                            soldiers[y][x] -= attacker;
                                        } else if (soldiers[y][x] != 1) {
                                            attacker = soldiers[y][x] - 1;
                                            soldiers[y][x] -= attacker;
                                        } else if (soldiers[y][x] == 1) {
                                            attacker = 0;
                                        }
                                        //رندوم ریزی
                                        for (i = 0; i < 2; ++i) {
                                            array_defender[i] = rand() % 6;
                                        }
                                        for (i = 0; i < 3; ++i) {
                                            array_attacker[i] = rand() % 6;
                                        }
                                        sort(array_defender, 2);
                                        sort(array_attacker, 3);
                                        if ((defender == 1 && attacker != 0) || (defender == 2 && attacker == 1)) {
                                            attacker = attacker_battle(array_defender, 1, array_attacker, attacker);
                                            defender = defender_battle(array_defender, 1, array_attacker, defender);
                                        } else if (defender == 2 && attacker != 0) {
                                            attacker = attacker_battle(array_defender, 2, array_attacker, attacker);
                                            defender = defender_battle(array_defender, 2, array_attacker, defender);
                                        }
                                        //The Hejrat
                                        if (defender == 0 && soldiers[y][x + 1] == 0) {
                                            player_contries[countries[y][x + 1]]--;
                                            player_contries[countries[y][x]]++;
                                            soldiers[y][x + 1] = attacker;
                                            countries[y][x + 1] = countries[y][x];
                                        }
                                            //The Bargasht
                                        else {
                                            soldiers[y][x] += attacker;
                                            soldiers[y][x + 1] += defender;
                                        }
                                        al_rest(0.3);
                                        al_play_sample(warfare_sound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                                    }
                                }
                                al_draw_circle(200 * (x + 1) + 100, 100 * y + 50, 40, al_map_rgb(0, 0, 0), 5);
                            }
                            ///////////////////////////////////////////////////////////////////////////////////LEFT
                            if (countries[y][x - 1] != THESEA && x - 1 >= 0 &&
                                countries[y][x - 1] != countries[y][x]) {
                                if (al_mouse_button_down(&statemouse, 1)) {
                                    if (statemouse.x >= 200 * (x - 1) && statemouse.x <= 200 * x &&
                                        statemouse.y >= 100 * y && statemouse.y <= 100 * (y + 1)) {
                                        //تعیین تعداد سرباز های مدافع
                                        if (soldiers[y][x - 1] >= 2) {
                                            defender = 2;
                                            soldiers[y][x - 1] -= defender;
                                        } else {
                                            defender = 1;
                                            soldiers[y][x - 1] = 0;
                                        }
                                        //تعیین تعداد سرباز های مهاجم
                                        if (soldiers[y][x] >= 4) {
                                            attacker = 3;
                                            soldiers[y][x] -= attacker;
                                        } else if (soldiers[y][x] != 1) {
                                            attacker = soldiers[y][x] - 1;
                                            soldiers[y][x] -= attacker;
                                        } else if (soldiers[y][x] == 1) {
                                            attacker = 0;
                                        }
                                        //رندوم ریزی
                                        for (i = 0; i < 2; ++i) {
                                            array_defender[i] = rand() % 6;
                                        }
                                        for (i = 0; i < 3; ++i) {
                                            array_attacker[i] = rand() % 6;
                                        }
                                        sort(array_defender, 2);
                                        sort(array_attacker, 3);
                                        if ((defender == 1 && attacker != 0) || (defender == 2 && attacker == 1)) {
                                            attacker = attacker_battle(array_defender, 1, array_attacker, attacker);
                                            defender = defender_battle(array_defender, 1, array_attacker, defender);
                                        } else if (defender == 2 && attacker != 0) {
                                            attacker = attacker_battle(array_defender, 2, array_attacker, attacker);
                                            defender = defender_battle(array_defender, 2, array_attacker, defender);
                                        }
                                        //Enteghale sarbaz
                                        if (defender == 0 && soldiers[y][x - 1] == 0) {
                                            player_contries[countries[y][x - 1]]--;
                                            player_contries[countries[y][x]]++;
                                            soldiers[y][x - 1] = attacker;
                                            countries[y][x - 1] = countries[y][x];
                                        }
                                            //Bargasht sarbaz
                                        else {
                                            soldiers[y][x] += attacker;
                                            soldiers[y][x - 1] += defender;
                                        }
                                        al_rest(0.3);
                                        al_play_sample(warfare_sound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                                    }
                                }
                                al_draw_circle(200 * (x - 1) + 100, 100 * y + 50, 40, al_map_rgb(0, 0, 0), 5);
                            }
                        }
                    }
                    //Fortify
                    if (fortify_forever) {
                        attack_forever = false;
                        if (w) {
                            w = false;
                            y = 7328;
                            x = 6345;
                        }
                        //Mabdae fortify
                        if (origin) {
                            al_get_mouse_state(&statemouse);
                            if (al_mouse_button_down(&statemouse, 1)) {
                                for (i = 0; i < 7; i++) {
                                    for (j = 0; j < 6; j++) {
                                        if (statemouse.x >= 200 * j && statemouse.x <= 200 * (j + 1) &&
                                            statemouse.y >= 100 * i && statemouse.y <= 100 * (i + 1)) {
                                            if (player_turn == countries[i][j] && soldiers[i][j] != 1) {
                                                y = i + 1;
                                                x = j + 1;
                                                origin = false;
                                                circle_draw1 = true;
                                                destination = true;
                                            }
                                        }
                                    }
                                }
                                al_rest(0.3);
                            }
                        }
                        if (circle_draw1)
                            al_draw_circle(200 * (x - 1) + 100, 100 * (y - 1) + 50, 40, al_map_rgb(255, 255, 0),
                                           5);
                        if (destination) {
                            al_get_mouse_state(&statemouse);
                            if (al_mouse_button_down(&statemouse, 2)) {
                                for (i = 0; i < 7; i++) {
                                    for (j = 0; j < 6; j++) {
                                        if (statemouse.x >= 200 * j && statemouse.x <= 200 * (j + 1) &&
                                            statemouse.y >= 100 * i && statemouse.y <= 100 * (i + 1)) {
                                            //&& y != i + 1 && x != j + 1
                                            if (player_turn == countries[i][j]) {
                                                destination = false;
                                                circle_draw2 = true;
                                                m = i + 1;
                                                l = j + 1;
                                            }
                                        }
                                    }
                                }
                                al_rest(0.3);
                            }
                        }
                        if (circle_draw2)
                            al_draw_circle(200 * (l - 1) + 100, 100 * (m - 1) + 50, 40, al_map_rgb(100, 100, 100),
                                           5);
//                        // && circle_draw1 && circle_draw2
                        if (!origin && !destination) {
                            /////por kardane dakhele fortify_countries
                            for (i = 0; i < 7; i++) {
                                for (j = 0; j < 6; j++) {
                                    fortify_countries[i + 1][j + 1] = countries[i][j];
                                }
                            }
                            //start finding a way !
                            ////jaye y vo x avaz shode !!!
//                            while (y != m || x != l) {
//                                //UP
//                                if (fortify_countries[y - 1][x] == fortify_countries[y][x]) {
//                                    //investigated(flag)
//                                    fortify_countries[y][x] = 4;
//                                    Hist[k][0] = y;
//                                    Hist[k][1] = x;
//                                    //shomarande history
//                                    k++;
//                                    y--;
//                                    continue;
//                                }
//                                //DOWN
//                                if (fortify_countries[y + 1][x] == fortify_countries[y][x]) {
//                                    fortify_countries[y][x] = 4;
//                                    //investigated(flag)
//                                    Hist[k][0] = y;
//                                    Hist[k][1] = x;
//                                    //shomarande history
//                                    k++;
//                                    y++;
//                                    continue;
//                                }
//                                //RIGHT
//                                if (fortify_countries[y][x + 1] == fortify_countries[y][x]) {
//                                    //investigated(flag)
//                                    fortify_countries[y][x] = 4;
//                                    Hist[k][0] = y;
//                                    Hist[k][1] = x;
//                                    //shomarande history
//                                    k++;
//                                    x++;
//                                    continue;
//                                }
//                                //LEFT
//                                if (fortify_countries[y][x - 1] == fortify_countries[y][x]) {
//                                    //investigated(flag)
//                                    fortify_countries[y][x] = 4;
//                                    Hist[k][0] = y;
//                                    Hist[k][1] = x;
//                                    //shomarande history
//                                    k++;
//                                    x--;
//                                    continue;
//                                }
//                                //go back to perevious block
//                                k--;
//                                if (k < 0) {
//                                    break;
//                                }
//                                //The Bon Bast(flag)
//                                fortify_countries[y][x] = 10;
//                                y = Hist[k][0];
//                                x = Hist[k][1];
//                            }
//                            The Pirouzi
//                            if (k > 0) {
                            fortify_forever = false;
                            soldiers[m - 1][l - 1] += (soldiers[y - 1][x - 1] - 1);
                            soldiers[y - 1][x - 1] = 1;
                            al_draw_line((x - 1) * 200 + 140, (y - 1) * 100 + 60, (l - 1) * 200 + 60,
                                         (m - 1) * 100 + 40,
                                         al_map_rgb(100, 200, 0), 5);
                                origin = false;
                                circle_draw1 = false;
                                destination = false;
                                circle_draw2 = false;
//                        }
//                        //The Shekast
//                            if (k < 0) {
//                                result = al_show_native_message_box(display, " Fortify ", " ",
//                                                                    "Fortify Impossible !",
//                                                                    0,
//                                                                    ALLEGRO_MESSAGEBOX_WARN);
//                                if (result == 1) {
//                                    mabda = true;
//                                    circle_draw1 = false;
//                                    circle_draw2 = false;
//                                } else {
//                                    mabda = false;
//                                    maghsad = false;
//                                }
//                            }
                        }
                    }
                    //Turn Receive
                    if (turn_receive && dor % number_of_players == 0 && dor != 0) {
                        turn_receive = false;
                        receive_forever = true;
                        attack_forever = false;
                        game_state = receive;
//                        player_turn = turn % number_of_players;
                        for (turn = 0; turn < number_of_players; turn++) {
                            ////////Shomaresh tedad keshvar ha !!
                            for (i = 0; i < 7; i++) {
                                for (j = 0; j < 6; j++) {
                                    if (turn == countries[i][j])
                                        player_contries[turn]++;
                                }
                            }
                            for (i = 0; i < 7; i++) {
                                for (j = 0; j < 6; j++) {
                                    ////////////USA
                                    if (countries[i][j] == countries[0][0] &&
                                        countries[i][j] == countries[0][1] &&
                                        countries[i][j] == countries[1][0] &&
                                        countries[i][j] == countries[1][1] &&
                                        countries[i][j] == countries[2][0] &&
                                        countries[i][j] == countries[3][0] &&
                                        countries[i][j] == countries[4][0] &&
                                        countries[i][j] == countries[5][0] &&
                                        countries[i][j] == countries[5][1])
                                        ///flag dashtane ghare USA
                                        player_continent_conquer[turn][1] = 1;

                                    //////////ASIA
                                    if (countries[i][j] == countries[0][4] &&
                                        countries[i][j] == countries[0][5] &&
                                        countries[i][j] == countries[1][4] &&
                                        countries[i][j] == countries[1][5] &&
                                        countries[i][j] == countries[2][4] &&
                                        countries[i][j] == countries[2][5] &&
                                        countries[i][j] == countries[3][4] &&
                                        countries[i][j] == countries[3][5])
                                        ///flag dashtane ghare ASIA
                                        player_continent_conquer[turn][2] = 1;

                                    //////////AFRICA
                                    if (countries[i][j] == countries[3][3] &&
                                        countries[i][j] == countries[4][2] &&
                                        countries[i][j] == countries[4][3] &&
                                        countries[i][j] == countries[5][2] &&
                                        countries[i][j] == countries[5][3] &&
                                        countries[i][j] == countries[6][2])
                                        ///flag dashtane ghare AFRICA
                                        player_continent_conquer[turn][3] = 1;

                                    ////////EUROPE
                                    if (countries[i][j] == countries[0][2] &&
                                        countries[i][j] == countries[0][3] &&
                                        countries[i][j] == countries[1][2] &&
                                        countries[i][j] == countries[1][3] &&
                                        countries[i][j] == countries[2][2] &&
                                        countries[i][j] == countries[2][3])
                                        ///flag dashtane ghare EUROPE
                                        player_continent_conquer[turn][4] = 1;
                                    ////////Emtiyaz USA
                                    if (player_continent_conquer[turn][1] == 1)
                                        player_soldiers[turn] = player_contries[turn] / 3 + 3;
                                    ////////Emtiyaz ASIA
                                    if (player_continent_conquer[turn][2] == 1)
                                        player_soldiers[turn] = player_contries[turn] / 3 + 4;
                                    ////////Emtiyaz AFRICA
                                    if (player_continent_conquer[turn][3] == 1)
                                        player_soldiers[turn] = player_contries[turn] / 3 + 2;
                                    ////////Emtiyaz EUROPE
                                    if (player_continent_conquer[turn][4] == 1)
                                        player_soldiers[turn] = player_contries[turn] / 3 + 4;
                                        ///////sarbaz dehi bedune dashtane ghare
                                    else {
                                        player_soldiers[turn] = player_contries[turn] / 3;
                                    }
                                }
                            }
                            players_zero_counter[turn] = 1 ;
                        }
                        turn = 0;
                    }
                    for (i = 0; i < 7; i++) {
                        for (j = 0; j < 6; j++) {
                            ////////////USA
                            if (countries[i][j] == countries[0][0] &&
                                countries[i][j] == countries[0][1] &&
                                countries[i][j] == countries[1][0] &&
                                countries[i][j] == countries[1][1] &&
                                countries[i][j] == countries[2][0] &&
                                countries[i][j] == countries[3][0] &&
                                countries[i][j] == countries[4][0] &&
                                countries[i][j] == countries[5][0] &&
                                countries[i][j] == countries[5][1])
                                ///flag dashtane ghare USA
                                player_continent_conquer[turn][1] = 1;

                            //////////ASIA
                            if (countries[i][j] == countries[0][4] &&
                                countries[i][j] == countries[0][5] &&
                                countries[i][j] == countries[1][4] &&
                                countries[i][j] == countries[1][5] &&
                                countries[i][j] == countries[2][4] &&
                                countries[i][j] == countries[2][5] &&
                                countries[i][j] == countries[3][4] &&
                                countries[i][j] == countries[3][5])
                                ///flag dashtane ghare ASIA
                                player_continent_conquer[turn][2] = 1;

                            //////////AFRICA
                            if (countries[i][j] == countries[3][3] &&
                                countries[i][j] == countries[4][2] &&
                                countries[i][j] == countries[4][3] &&
                                countries[i][j] == countries[5][2] &&
                                countries[i][j] == countries[5][3] &&
                                countries[i][j] == countries[6][2])
                                ///flag dashtane ghare AFRICA
                                player_continent_conquer[turn][3] = 1;

                            ////////EUROPE
                            if (countries[i][j] == countries[0][2] &&
                                countries[i][j] == countries[0][3] &&
                                countries[i][j] == countries[1][2] &&
                                countries[i][j] == countries[1][3] &&
                                countries[i][j] == countries[2][2] &&
                                countries[i][j] == countries[2][3])
                                ///flag dashtane ghare EUROPE
                                player_continent_conquer[turn][4] = 1;
                            ////////Emtiyaz USA
                            if (player_continent_conquer[turn][1] == 1)
                                player_soldiers[turn] = player_contries[turn] / 3 + 3;
                            ////////Emtiyaz ASIA
                            if (player_continent_conquer[turn][2] == 1)
                                player_soldiers[turn] = player_contries[turn] / 3 + 4;
                            ////////Emtiyaz AFRICA
                            if (player_continent_conquer[turn][3] == 1)
                                player_soldiers[turn] = player_contries[turn] / 3 + 2;
                            ////////Emtiyaz EUROPE
                            if (player_continent_conquer[turn][4] == 1)
                                player_soldiers[turn] = player_contries[turn] / 3 + 4;
                                ///////sarbaz dehi bedune dashtane ghare
                            else {
                                player_soldiers[turn] = player_contries[turn] / 3;
                            }
                        }
                    }
                    //////////////////////////////////////// sharte borde bazi ///////////////////////////////////////////
                    for (int n = 0; n < 4; ++n) {
                        r = 0;
                        for (int y = 1; y < 4; ++y) {
                            if (player_continent_conquer[n][1] == player_continent_conquer[n][y + 1] &&
                                player_continent_conquer[n][y + 1] != 0) {
                                r++;
                            }
                            if (r == 4) {
                                winner = n;
                                page_switch = Winner_page;
                            }
                        }
                    }
                    //gushe samte rast
                    al_get_mouse_state(&statemouse);
                    if (al_mouse_button_down(&statemouse, 1)) {
                        //The Info_menu
                        if (statemouse.x >= 1275 && statemouse.x <= 1340 && statemouse.y >= 2 &&
                            statemouse.y <= 60) {
                            page_switch = Info_menu;
                        }
                        //The Help_menu
                        if (statemouse.x >= 1350 && statemouse.x <= 1410 && statemouse.y >= 2 &&
                            statemouse.y <= 60) {
                            page_switch = help_menu;
                            help_menu_switch = help_menu1;
                        }
                        //The Pause
                        if (statemouse.x >= 1420 && statemouse.x <= 1490 && statemouse.y >= 2 &&
                            statemouse.y <= 60) {
                            page_switch = pause_menu;
                        }
                        al_rest(0.1);
                    }
                    break;
                case pause_menu:
                    al_draw_bitmap(Risk_pause_menu, 0, 0, 0);
                    al_get_mouse_state(&statemouse);
                    if (al_mouse_button_down(&statemouse, 1)) {
                        if (statemouse.x <= 900 && statemouse.x >= 600 && statemouse.y <= 450 &&
                            statemouse.y >= 380)                          // Resume
                        {
                            page_switch = map;
                        }
//                    if (curX <= 900 && curX >= 600 && curY <= 570 && curY >= 515)                 // Save Game
//                    {
//                    }
                        if (statemouse.x <= 900 && statemouse.x >= 600 && statemouse.y <= 690 &&
                            statemouse.y >= 635)                         // Main Menu
                        {
                            result = al_show_native_message_box(display, "Risk Game Pause", "Warning",
                                                                "Closing the game from the pause menu can damage your data \n\t\t\t\tBack to Main Menu?",
                                                                0,
                                                                ALLEGRO_MESSAGEBOX_WARN |
                                                                ALLEGRO_MESSAGEBOX_YES_NO);
                            if (result == 1) {
                                turn = 0;
                                taghsim_sarbaz_keshvar = true;
                                random_dehi = true;
                                first_soldier_conscription = true;
                                receive_forever = true;
                                fortify_forever = false;
                                attack_forever = false;
                                game_state = receive;
                                page_switch = main_menu;
                            } else
                                page_switch = pause_menu;
                        }
                        al_rest(0.3);
                    }
                    break;
                case help_menu:
                    al_get_mouse_state(&statemouse);
                    if (al_mouse_button_down(&statemouse, 1)) {
                        if (statemouse.x >= 20 && statemouse.x <= 90 && statemouse.y >= 20 &&
                            statemouse.y <= 90) {
                            page_switch = map;
                            help_menu_switch = 55;
                        }
                        al_rest(0.3);
                    }
                    switch (help_menu_switch) {
                        case help_menu1:
                            al_draw_bitmap(Help_menu1, 0, 0, 0);
                            if (al_mouse_button_down(&statemouse, 1)) {
                                if (statemouse.x >= 1420 && statemouse.x <= 1460 && statemouse.y >= 400 &&
                                    statemouse.y <= 440) {
                                    help_menu_switch = help_menu2;
                                }
                                al_rest(0.3);
                            }
                            break;
                        case help_menu2:
                            al_draw_bitmap(Help_menu2, 0, 0, 0);
                            if (al_mouse_button_down(&statemouse, 1)) {
                                if (statemouse.x >= 20 && statemouse.x <= 60 && statemouse.y >= 400 &&
                                    statemouse.y <= 440) {
                                    help_menu_switch = help_menu1;
                                }
                                if (statemouse.x >= 1420 && statemouse.x <= 1460 && statemouse.y >= 400 &&
                                    statemouse.y <= 440) {
                                    help_menu_switch = help_menu3;
                                }
                                al_rest(0.3);
                            }
                            break;
                        case help_menu3:
                            al_draw_bitmap(Help_menu3, 0, 0, 0);
                            if (al_mouse_button_down(&statemouse, 1)) {
                                if (statemouse.x >= 30 && statemouse.x <= 70 && statemouse.y >= 400 &&
                                    statemouse.y <= 440) {
                                    help_menu_switch = help_menu2;
                                }
                                if (statemouse.x >= 1420 && statemouse.x <= 1460 && statemouse.y >= 400 &&
                                    statemouse.y <= 440) {
                                    help_menu_switch = help_menu4;
                                }
                                al_rest(0.3);
                            }
                            break;
                        case help_menu4:
                            al_draw_bitmap(Help_menu4, 0, 0, 0);
                            if (al_mouse_button_down(&statemouse, 1)) {
//                                if (statemouse.x >= 20 && statemouse.x <= 90 && statemouse.y >= 20 &&
//                                    statemouse.y <= 90) {
//                                    page_switch = map;
//                                    help_menu_switch = 55;
//                                }
                                if (statemouse.x >= 30 && statemouse.x <= 70 && statemouse.y >= 400 &&
                                    statemouse.y <= 440) {
                                    help_menu_switch = help_menu3;
                                }
                                al_rest(0.3);
                            }
                            break;
                        default:
                            page_switch = map;
                    }
                    break;
                case Info_menu:
                    al_draw_bitmap(info_menu, 0, 0, 0);
                    al_get_mouse_state(&statemouse);
                    if (al_mouse_button_down(&statemouse, 1)) {
                        if (statemouse.x >= 20 && statemouse.x <= 70 && statemouse.y >= 20 &&
                            statemouse.y <= 70) {
                            page_switch = map;
                        }
                        al_rest(0.3);
                    }
                    break;
                case Winner_page:
                    if (winner == 0) {
                        al_draw_bitmap(winner_page1, 0, 0, 0);
                        al_play_sample(winner_music, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                    } else if (winner == 1) {
                        al_draw_bitmap(winner_page2, 0, 0, 0);
                        al_play_sample(winner_music, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                    } else if (winner == 2) {
                        al_draw_bitmap(winner_page3, 0, 0, 0);
                        al_play_sample(winner_music, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                    } else if (winner == 3) {
                        al_draw_bitmap(winner_page4, 0, 0, 0);
                        al_play_sample(winner_music, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    al_get_mouse_state(&statemouse);
                    if (al_mouse_button_down(&statemouse, 1)) {
                        if (statemouse.x >= 20 && statemouse.x <= 70 && statemouse.y >= 20 &&
                            statemouse.y <= 70) {
                            page_switch = main_menu;
                        }
                        al_rest(0.3);
                    }
                    break;
                default:
                    al_show_native_message_box(display, game_title, "ERROR",
                                               "Sorry an Unexpected ERROR has happened\n Please try to restart the game... ",
                                               (const char *) ALLEGRO_MESSAGEBOX_WARN, 0);
            }
            al_flip_display();
        }

    }

//uninstall & destroy
    al_uninstall_keyboard();

    al_uninstall_mouse();

    al_uninstall_audio();

    al_destroy_bitmap(soldier_image);
    al_destroy_bitmap(background_sea);
    al_destroy_bitmap(map_background);
    al_destroy_bitmap(Help_menu1);
    al_destroy_bitmap(Help_menu2);
    al_destroy_bitmap(Help_menu3);
    al_destroy_bitmap(Help_menu4);
    al_destroy_bitmap(info_menu);
    al_destroy_bitmap(profile_abi);
    al_destroy_bitmap(profile_sabz);
    al_destroy_bitmap(profile_banafsh);
    al_destroy_bitmap(profile_ghermez);
    al_destroy_bitmap(Risk_player_menu);
    al_destroy_bitmap(Risk_pause_menu);
    al_destroy_bitmap(winner_page1);
    al_destroy_bitmap(winner_page2);
    al_destroy_bitmap(winner_page3);
    al_destroy_bitmap(winner_page4);
    al_destroy_sample(warfare_sound);
    al_destroy_sample(winner_music);
    al_destroy_audio_stream(background_music);
    al_destroy_bitmap(Risk_menu);
    al_destroy_font(font2);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    return 0;
}

//bubble sort
void sort(int array[], int size) {
    int temp;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (array[j] > array[i]) {
                temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
        }
    }
}

int defender_battle(int array_defender[], int size1, int array_attacker[], int defender) {
    for (int i = 0; i < size1; ++i) {
        if (array_defender[i] < array_attacker[i]) {
            defender--;
        }
    }
    return defender;
}

int attacker_battle(int array_defender[], int size1, int array_attacker[], int attacker) {
    for (int i = 0; i < size1; ++i) {
        if (array_defender[i] >= array_attacker[i]) {
            attacker--;
        }
    }
    return attacker;
}

void draw_black_borders() {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (!(i >= 2 && i <= 4 && j == 1) && !(j >= 0 && j <= 1 && i == 6) && !(j == 2 && i == 3) &&
                !(i == 6 && j == 3) &&
                !(i >= 4 && i <= 6 && j >= 4 && j <= 5)) {
                al_draw_rectangle(j * 200, i * 100, (j + 1) * 200, (i + 1) * 100, al_map_rgb(0, 0, 0), 1);
            }
        }
    }
}

//void player_countries_changer(int player_soldiers[4], int player_turn) {
//    player_soldiers[player_turn]--;
//}

//void state_box(int pos_x, int pos_y, char state) {
//    const ALLEGRO_FONT *const font;
//    al_draw_filled_rounded_rectangle(400, 740, 800, 800, 8, 8, al_map_rgb(175, 19, 114));
//    al_draw_filled_rectangle(pos_x, pos_y, pos_x + 130, pos_y + 10, al_map_rgb(244, 74, 250));
//    if (pos_x < 535 || state == 'R')
//        al_draw_text(font, al_map_rgb(255, 255, 255), 580, 760, 0, "Receive");
//    if (pos_x < 665 && pos_x >= 535 || state == 'A')
//        al_draw_text(font, al_map_rgb(255, 255, 255), 580, 760, 0, "Attack");
//    if (pos_x < 795 && pos_x >= 665 || state == 'F')
//        al_draw_text(font, al_map_rgb(255, 255, 255), 580, 760, 0, "Fortify");
//    if (pos_x >= 795)
//        pos_x = 405;
//    al_flip_display();
//}
//void print_turn_box(int turn) {
//    if (turn == 0)
//        al_draw_filled_rounded_rectangle(1230, 80, 1490, 250, 15, 15, al_map_rgb(255, 255, 0));
//    if (turn == 1)
//        al_draw_filled_rounded_rectangle(1230, 250, 1490, 520, 15, 15, al_map_rgb(255, 255, 0));
//    if (turn == 2)
//        al_draw_filled_rounded_rectangle(1230, 420, 1490, 690, 15, 15, al_map_rgb(255, 255, 0));
//    if (turn == 3)
//        al_draw_filled_rounded_rectangle(1230, 590, 1490, 760, 15, 15, al_map_rgb(255, 255, 0));
//}