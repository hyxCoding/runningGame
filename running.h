#ifndef RUNNING_H
#define RUNNING_H
#include "gameEngine.h"
#include <time.h>//计时
#include <math.h>//计算

static const int MAX_INT = 0x7fffffff;
static const int MAX_JUMP_CNT = 25;
static const int MAX_ANIM_CNT = 8;
static const int ADD_SCORE = 100;
static const int BACKGROUND_SIZE = 8;
static const int WALL_SIZE = 4;
static const int ENEMY_SIZE = 3;
static const int BUFFER_SIZE = 512;
static const int ANIMATIONS_SIZE = 5;
static const int CHANNELS = 16;
static const int SCREEN_WIDTH = 900;
static const int SCREEN_HEIGHT = 600;
static const int BACKGROUND_WIDTH = 1152;
static const int BACKGROUND_HEIGHT = 648;
static const int WALL_WIDTH = 500;
static const int WALL_HEIGHT = 48;
static const int ENEMY_1_WIDTH = 145;
static const int ENEMY_1_HEIGHT = 61;
static const int ENEMY_2_WIDTH = 75;
static const int ENEMY_2_HEIGHT = 31;
static const int ENEMY_3_WIDTH = 100;
static const int ENEMY_3_HEIGHT = 50;
static const int UI_HELICOPTER_WIDTH = 192;
static const int UI_HELICOPTER_HEIGHT = 64;
static const int EFFECT_1_WIDTH = 32;
static const int EFFECT_1_HEIGHT = 32;
static const int UI_TEA_WIDTH = 33;
static const int UI_TEA_HEIGHT = 68;
static const int UI_START_ICON_WIDTH = 100;
static const int UI_START_ICON_HEIGHT = 100;
static const int UI_HELP_ICON_WIDTH = 100;
static const int UI_HELP_ICON_HEIGHT = 100;
static const int UI_CONTINUE_ICON_WIDTH = 100;
static const int UI_CONTINUE_ICON_HEIGHT = 100;
static const int UI_QUIT_ICON_WIDTH = 100;
static const int UI_QUIT_ICON_HEIGHT = 100;
static const int UI_HELP_PAGE_WIDTH = 500;
static const int UI_HELP_PAGE_HEIGHT = 200;
static const int UI_TITLE_WIDTH = 300;
static const int UI_TITLE_HEIGHT = 110;
static const int COIN_WIDTH = 18;
static const int COIN_HEIGHT = 18;
static const int TEA_WIDTH = 16;
static const int TEA_HEIGHT = 34;
static const int PLAYER_WIDTH = 72;
static const int PLAYER_HEIGHT = 72;
static const int IN_WORLD = 1;
static const int IN_SCREEN = 0;
static const int TEA_SUMMON_RATIO = 10;//十分之一概率生成冰红茶
static const int MAX_TEA_CNT = 3;//冰红茶最多数量
static const int MAX_SKILL_CNT = 600;//技能持续帧数,每帧16.6ms
static const int MAX_SUMMON_EFFECT_1_CNT = 10;//特效生成间隔
static const int FONT_SIZE = 24;//字体大小
static const int MAX_STR_LEN = 20;//数组最大长度
static const double GRAVITY = 5.5;//重力加速度
static const double LIMIT = 1.0;
static const double JUMP_HEIGHT = 100.0;//跳跃高度,用于防止墙壁生成太高
static const double RUN_ZOOM_W = 0.4;//不同动作时的碰撞体积缩放
static const double RUN_ZOOM_H = 0.9;
static const double JUMP_ZOOM_W = 0.2;
static const double JUMP_ZOOM_H = 0.5;
static const double CROUCH_ZOOM_W = 1.5;
static const double CROUCH_ZOOM_H = 0.5;
static const double SPEED_PLAYER = 5;
static const double SPEED_BACKGROUND_1 = 0.5;
static const double SPEED_BACKGROUND_2 = 1;
static const double SPEED_BACKGROUND_3 = 1.5;
static const double SPEED_BACKGROUND_4 = 2;
static const double SPEED_BACKGROUND_5 = 2.5;
static const double SPEED_BACKGROUND_6 = 3;
static const double SPEED_BACKGROUND_7 = 3.5;
static const double SPEED_BACKGROUND_8 = 5;
static const double SUMMON_WALL_DIST_X = 1600.0;//如果pre_wall_pos.x - player.x < 这个值,生成新墙
static const double ADD_WALL_POS_X = 635;//每次生成wall后pos.x的增量
static const double MAX_SUMMON_Y = 400.0;//最大生成Y
static const double MIN_SUMMON_Y = 200.0;//最小生成Y
static const double MIN_HELICOPTER_Y = 100;//直升机上升最大高度
static const double SUMMON_HELICOPTER_X = 450;
static const double SUMMON_HELICOPTER_Y = 700;
static const double UI_START_ICON_X = 450;
static const double UI_START_ICON_Y = 450;
static const double UI_HELP_ICON_X = 350;
static const double UI_HELP_ICON_Y = 450;
static const double UI_CONTINUE_ICON_X = 350;
static const double UI_CONTINUE_ICON_Y = 450;
static const double UI_QUIT_ICON_X = 550;
static const double UI_QUIT_ICON_Y = 450;
static const double UI_HELP_PAGE_X = 450;
static const double UI_HELP_PAGE_Y = 300;
static const double UI_TITLE_X = 450;
static const double UI_TITLE_Y = 100;
static const double UI_SCORE_X = 800;
static const double UI_SCORE_Y = 50;
static const double UI_TIME_X = 100;
static const double UI_TIME_Y = 50;
static const struct Color WHITE = {255,255,255,255};

char score_str[20] = "0";//分数数组
char live_time_str[20] = "00:00:00";//时间数组

time_t begin_time;//开始游戏时间
int quit_game_flag = 0;
int player_alive = 0;
int live_time = -1;//存活时间,-1是为了显示0,预加载1
int score = 0;//得分
int onWall = 1;//在地上
int onAir = 0;//在天上
int onSkill = 0;//使用技能中
int onHelicopter = 0;//在坐直升机
int raising = 0;
int falling = 0;
int jump_cnt = 0;
int tea_cnt = 0;
int skill_cnt = 0;//技能持续时间计数器
int summon_effect_1_cnt = 0;
struct PointF pre_wall_pos;//上一次生成墙壁的位置
struct PointF pre_player_pos;//上次玩家位置
struct Point center_pos = {SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2};
struct PaintManager paintManager;//绘图管理器
struct EntityManager entityManager;//实体管理器
struct AudioManager audioManager;//音频管理器
struct InputManager inputManager;//(键盘，鼠标)输入管理器
struct FontManager fontManager;//字体管理器

struct Texture *effect_1_texture = NULL;

struct Animation *coin_animation = NULL;
struct Animation *tea_animation = NULL;
struct Animation *tea_ui_animation = NULL;
struct Animation *player_run_animation = NULL;
struct Animation *player_jump_animation = NULL;
struct Animation *player_crouch_animation = NULL;
struct Entity *entity = NULL;//用于临时存储
struct Entity *player = NULL;
struct Entity *start_button = NULL;
struct Entity *continue_button = NULL;
struct Entity *help_button = NULL;
struct Entity *quit_button = NULL;
struct Entity *help_page = NULL;
struct Entity *helicopter_ui = NULL;
struct Entity *title = NULL;
struct Entity *score_ui = NULL;
struct Entity *front_time_ui = NULL;//前缓冲
struct Entity *back_time_ui = NULL;//后缓冲,避免字体纹理加载过慢导致闪烁
struct Window *window = NULL;
struct Renderer *renderer = NULL;


char path_font[] = "resource/font/0.ttf";
char *path_background[] = {
    "resource/background/1.png","resource/background/2.png",
    "resource/background/3.png","resource/background/4.png",
    "resource/background/5.png","resource/background/6.png",
    "resource/background/7.png","resource/background/8.png"
};//背景资源路径

char *path_enemy[] = {
    "resource/enemy/1.png","resource/enemy/2.png","resource/enemy/3.png",
};
char *path_wall[] = {
    "resource/wall/1.png","resource/wall/2.png",
    "resource/wall/3.png","resource/wall/4.png"
};//墙
char path_player_jump[] = "resource/player/jump.png";
char path_player_run[] = "resource/player/run.png";
char path_player_crouch[] = "resource/player/crouch.png";
char path_coin[] = "resource/item/coin.png";
char path_tea[] = "resource/item/tea.png";
char path_helicopter_ui[] = "resource/ui/0.png";
char path_tea_ui[] = "resource/ui/1.png";
char path_effect_1[] = "resource/effect/1.png";
char path_bgm[] = "resource/audio/music/bgm.mp3";
char path_chunk_helicopter[] = "resource/audio/chunk/helicopter.mp3";
char path_chunk_death[] = "resource/audio/chunk/death.mp3";
char path_chunk_collision[] = "resource/audio/chunk/collision.mp3";
char path_chunk_coin[] = "resource/audio/chunk/coin.mp3";
char path_chunk_jump[] = "resource/audio/chunk/jump.mp3";
char path_start_icon[] = "resource/ui/start.png";
char path_help_icon[] = "resource/ui/help.png";
char path_continue_icon[] = "resource/ui/continue.png";
char path_quit_icon[] = "resource/ui/quit.png";
char path_help_page[] = "resource/ui/help_page.png";
char path_title[] = "resource/ui/title.png";

int enemy_width[] = {ENEMY_1_WIDTH,ENEMY_2_WIDTH,ENEMY_3_WIDTH};
int enemy_height[] = {ENEMY_1_HEIGHT,ENEMY_2_HEIGHT,ENEMY_3_HEIGHT};

double speed_background[] = {
    SPEED_BACKGROUND_1,SPEED_BACKGROUND_2,
    SPEED_BACKGROUND_3,SPEED_BACKGROUND_4,
    SPEED_BACKGROUND_5,SPEED_BACKGROUND_6,
    SPEED_BACKGROUND_7,SPEED_BACKGROUND_8
};


struct Animation *wall_animations[4] = {};
struct Animation *enemy_animations[3] = {};

struct Entity *tea_ui[3] = {};
struct Entity *background[8] = {};

enum EntityType{//实体类型
    Entity_NONE = -1,
    BACKGROUND,
    PLAYER,
    ENEMY,
    WALL,
    EFFECT,
    ITEM,
    UI
};

enum AnimationType{//动画类型
    Animation_NONE = -1,
    RUN,
    JUMP,
    CROUCH,
    DEATH,
    IDLE
};

enum zValueType{//z值类型
    Z_NONE = -1,
    Z_BACKGROUND_1,
    Z_BACKGROUND_2,
    Z_BACKGROUND_3,
    Z_BACKGROUND_4,
    Z_BACKGROUND_5,
    Z_BACKGROUND_6,
    Z_BACKGROUND_7,
    Z_BACKGROUND_8,
    Z_WALL,
    Z_EFFECT,
    Z_ENEMY,
    Z_ITEM,
    Z_PLAYER,
    Z_UI
};

enum ItemKind{
    I_NONE = -1,
    TEA
};

enum AudioType{
    A_NONE = -1,
    CHUNK,
    MUSIC
};

enum AudioIndex{
    AI_NONE = -1,
    BGM,
    CHUNK_JUMP,
    CHUNK_HELICOPTER,
    CHUNK_DEATH,
    CHUNK_COIN,
    CHUNK_COLLISION
};

void update_player(struct Entity *_this,struct EntityManager *manager);
void update_enemy(struct Entity *_this,struct EntityManager *manager);
void update_item(struct Entity *_this,struct EntityManager *manager);
void update_ui(struct Entity *_this,struct EntityManager *manager);
void update_wall(struct Entity *_this,struct EntityManager *manager);
void update_effect(struct Entity *_this,struct EntityManager *manager);
void update_background(struct Entity *_this,struct EntityManager *manager);
void load_resource();
void init_game();
void reset_game();
void menu_loop();//菜单界面循环
void game_loop();//游戏界面循环
void help_loop();//帮助界面循环
void game();
void random_wall_summon();
void finish_skill();
void cast_skill();
void summon_effect_1();
void ride_helicopter();
void leave_helicopter();

void int_to_string(int x,char str[]){
    if(x == 0){
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    int size = 0;
    int tmp = x;
    while(tmp){
        size++;
        tmp /= 10;
    }
    str[size--] = '\0';
    tmp = x;
    while(tmp){
        str[size--] = '0' + tmp % 10;
        tmp /= 10;
    }
    return;
}

void update_time_str(int x){//更新时间字符串
    int h = x / 3600;
    int m = (x % 3600) / 60;
    int s = x % 60;
    live_time_str[0] = '0' + h / 10;
    live_time_str[1] = '0' + h % 10;
    live_time_str[3] = '0' + m / 10;
    live_time_str[4] = '0' + m % 10;
    live_time_str[6] = '0' + s / 10;
    live_time_str[7] = '0' + s % 10;
    return;
}

int click_button(int s_x,int s_y,int t_x,int t_y,int h_w,int h_h){
    return (abs(s_x - t_x) < h_w && abs(s_y - t_y) < h_h);
}

void clear_old_entity(){//清除旧实体
    struct List_Entity *list = entityManager.list_entity;
    struct Node_Entity *cur = list->head;
    for(int i = 0;i < list->size;i++,cur = cur->next){
        if(cur->entity->type == ITEM || cur->entity->type == WALL || cur->entity->type == ENEMY){
            cur->entity->deleteLater = 1;
        }  
    }
    return;
}

void update_time_ui(){
    if(!player_alive){
        return;
    }
    int n_t = time(NULL) - begin_time;
    if(n_t == live_time){//时间没变
        return;
    }
    live_time = n_t;
    if(front_time_ui){
        front_time_ui->deleteLater = 1;
    }
    front_time_ui = back_time_ui;
    if(front_time_ui){
        front_time_ui->visible = 1;
    }
    update_time_str(live_time + 1);//预加载下一秒图片
    struct Texture *time_icon = fontManager.createTexture(&fontManager,WHITE,live_time_str,FONT_SIZE);
    int w = time_icon->w;
    int h = time_icon->h;
    back_time_ui = entityManager.create(&entityManager,w,h,UI,1,0,ANIMATIONS_SIZE,0,UI_TIME_X,UI_TIME_Y,&update_ui);
    back_time_ui->currentAnim = back_time_ui->animations[0] = newAnimation(w,h,1,1,0,time_icon);
    back_time_ui->visible = 0;
    return;
}

void update_score_ui(){//更新分数显示
    int_to_string(score,score_str);
    if(score_ui){
        score_ui->deleteLater = 1;
    }
    struct Texture *score_icon = fontManager.createTexture(&fontManager,WHITE,score_str,FONT_SIZE);
    int w = score_icon->w;
    int h = score_icon->h;
    score_ui = entityManager.create(&entityManager,w,h,UI,1,0,ANIMATIONS_SIZE,0,UI_SCORE_X,UI_SCORE_Y,&update_ui);
    score_ui->currentAnim = score_ui->animations[0] = newAnimation(w,h,1,1,0,score_icon);
    return;
}

void load_resource(){
    effect_1_texture = newTexture(renderer,path_effect_1,1);

    coin_animation = newAnimation(COIN_WIDTH,COIN_HEIGHT,9,1,1,newTexture(renderer,path_coin,1));
    tea_animation = newAnimation(TEA_WIDTH,TEA_HEIGHT,1,1,1,newTexture(renderer,path_tea,1));
    player_run_animation = newAnimation(PLAYER_WIDTH,PLAYER_HEIGHT,6,1,1,newTexture(renderer,path_player_run,1));
    player_jump_animation = newAnimation(PLAYER_WIDTH,PLAYER_HEIGHT,4,0,1,newTexture(renderer,path_player_jump,1));
    player_crouch_animation = newAnimation(PLAYER_WIDTH,PLAYER_HEIGHT,1,1,1,newTexture(renderer,path_player_crouch,1));
    tea_ui_animation = newAnimation(UI_TEA_WIDTH,UI_TEA_HEIGHT,1,1,1,newTexture(renderer,path_tea_ui,1)); 
    for(int i = 0;i < ENEMY_SIZE;i++){
        enemy_animations[i] = 
        newAnimation(enemy_width[i],enemy_height[i],1,1,1,newTexture(renderer,path_enemy[i],1));
    }
    for(int i = 0;i < WALL_SIZE;i++){
        wall_animations[i] = 
        newAnimation(WALL_WIDTH,WALL_HEIGHT,1,1,1,newTexture(renderer,path_wall[i],1));
    }
    for(int i = 0;i < BACKGROUND_SIZE;i++){//加载背景
        background[i] = entityManager.create(&entityManager,
        BACKGROUND_WIDTH,BACKGROUND_HEIGHT,BACKGROUND,1,1,ANIMATIONS_SIZE,speed_background[i],
        BACKGROUND_WIDTH / 2.0,BACKGROUND_HEIGHT / 2.0,&update_background);
        background[i]->zValue = Z_BACKGROUND_8 - i;
        background[i]->currentAnim = background[i]->animations[0] =
        newAnimation(BACKGROUND_WIDTH,BACKGROUND_HEIGHT,1,1,0,newTexture(renderer,path_background[i],0));
    }
    for(int i = 0;i < MAX_TEA_CNT;i++){
        tea_ui[i] = entityManager.create(&entityManager,UI_TEA_WIDTH,UI_TEA_HEIGHT,
        UI,1,0,ANIMATIONS_SIZE,0,(i + 1) * 40,550,&update_ui);
        tea_ui[i]->currentAnim = tea_ui[i]->animations[0] = tea_ui_animation;
        tea_ui[i]->visible = 0;
    }

    helicopter_ui = entityManager.create(&entityManager,UI_HELICOPTER_WIDTH,UI_HELICOPTER_HEIGHT,
    UI,1,0,ANIMATIONS_SIZE,0,SCREEN_WIDTH / 2,UI_HELICOPTER_HEIGHT,&update_ui);
    helicopter_ui->currentAnim = helicopter_ui->animations[0] = 
    newAnimation(UI_HELICOPTER_WIDTH,UI_HELICOPTER_HEIGHT,8,1,0,newTexture(renderer,path_helicopter_ui,0));
    helicopter_ui->visible = 0;

    start_button = entityManager.create(&entityManager,UI_START_ICON_WIDTH,UI_START_ICON_HEIGHT,UI,1,0,
    ANIMATIONS_SIZE,0,UI_START_ICON_X,UI_START_ICON_Y,&update_ui);
    start_button->currentAnim = start_button->animations[0] = 
    newAnimation(UI_START_ICON_WIDTH,UI_START_ICON_HEIGHT,1,1,0,newTexture(renderer,path_start_icon,0));

    continue_button = entityManager.create(&entityManager,UI_CONTINUE_ICON_WIDTH,UI_CONTINUE_ICON_HEIGHT,UI,1,0,
    ANIMATIONS_SIZE,0,UI_CONTINUE_ICON_X,UI_CONTINUE_ICON_Y,&update_ui);
    continue_button->currentAnim = continue_button->animations[0] = 
    newAnimation(UI_CONTINUE_ICON_WIDTH,UI_CONTINUE_ICON_HEIGHT,1,1,0,newTexture(renderer,path_continue_icon,0));

    help_button = entityManager.create(&entityManager,UI_HELP_ICON_WIDTH,UI_HELP_ICON_HEIGHT,UI,1,0,
    ANIMATIONS_SIZE,0,UI_HELP_ICON_X,UI_HELP_ICON_Y,&update_ui);
    help_button->currentAnim = help_button->animations[0] =
    newAnimation(UI_HELP_ICON_WIDTH,UI_HELP_ICON_HEIGHT,1,1,0,newTexture(renderer,path_help_icon,0));

    quit_button = entityManager.create(&entityManager,UI_QUIT_ICON_WIDTH,UI_QUIT_ICON_HEIGHT,UI,1,0,
    ANIMATIONS_SIZE,0,UI_QUIT_ICON_X,UI_QUIT_ICON_Y,&update_ui);
    quit_button->currentAnim = quit_button->animations[0] =
    newAnimation(UI_QUIT_ICON_WIDTH,UI_QUIT_ICON_HEIGHT,1,1,0,newTexture(renderer,path_quit_icon,0));

    help_page = entityManager.create(&entityManager,UI_HELP_PAGE_WIDTH,UI_HELP_PAGE_HEIGHT,UI,
    1,0,ANIMATIONS_SIZE,0,UI_HELP_PAGE_X,UI_HELP_PAGE_Y,&update_ui);
    help_page->currentAnim = help_page->animations[0] =
    newAnimation(UI_HELP_PAGE_WIDTH,UI_HELP_PAGE_HEIGHT,1,1,0,newTexture(renderer,path_help_page,0));

    title = entityManager.create(&entityManager,UI_TITLE_WIDTH,UI_TITLE_HEIGHT,UI,
    1,0,ANIMATIONS_SIZE,0,UI_TITLE_X,UI_TITLE_Y,&update_ui);
    title->currentAnim = title->animations[0] =
    newAnimation(UI_TITLE_WIDTH,UI_TITLE_HEIGHT,1,1,0,newTexture(renderer,path_title,0));

    start_button->visible = 0;
    continue_button->visible = 0;
    help_button->visible = 0;
    quit_button->visible = 0;
    help_page->visible = 0;
    title->visible = 0;

    audioManager.addAudio(&audioManager,path_bgm,BGM,MUSIC);
    audioManager.addAudio(&audioManager,path_chunk_helicopter,CHUNK_HELICOPTER,CHUNK);
    audioManager.addAudio(&audioManager,path_chunk_collision,CHUNK_COLLISION,CHUNK);
    audioManager.addAudio(&audioManager,path_chunk_coin,CHUNK_COIN,CHUNK);
    audioManager.addAudio(&audioManager,path_chunk_death,CHUNK_DEATH,CHUNK);
    audioManager.addAudio(&audioManager,path_chunk_jump,CHUNK_JUMP,CHUNK);
    return;
}

void free_resource(){//只针对shared的Animation和Texture，其余由对应Manager自动释放
    deleteTexture(effect_1_texture);

    deleteTexture(coin_animation->spriteSheet);
    deleteAnimation(coin_animation);

    deleteTexture(tea_animation->spriteSheet);
    deleteAnimation(tea_animation);

    deleteTexture(player_run_animation->spriteSheet);
    deleteAnimation(player_run_animation);
    
    deleteTexture(player_jump_animation->spriteSheet);
    deleteAnimation(player_jump_animation);
    
    deleteTexture(player_crouch_animation->spriteSheet);
    deleteAnimation(player_crouch_animation);
    
    deleteTexture(tea_ui_animation->spriteSheet);
    deleteAnimation(tea_ui_animation);
    for(int i = 0;i < ENEMY_SIZE;i++){
        deleteTexture(enemy_animations[i]->spriteSheet);
        deleteAnimation(enemy_animations[i]);
    }
    for(int i = 0;i < WALL_SIZE;i++){
        deleteTexture(wall_animations[i]->spriteSheet);
        deleteAnimation(wall_animations[i]);
    }
    return;
}

void init_game(){
    srand(time(NULL));
    initEngine();
    window = newWindow("牢大快跑",SCREEN_WIDTH,SCREEN_HEIGHT);
    renderer = newRenderer(window);
    initPaintManager(&paintManager,center_pos,renderer,BUFFER_SIZE);
    initEntityManager(&entityManager);
    initAudioManager(&audioManager,BUFFER_SIZE,CHANNELS);
    initInputManager(&inputManager);
    initFontManager(&fontManager,renderer,BUFFER_SIZE,path_font);
    load_resource();
    return;
}

void quit_game(){
    destroyPaintManager(&paintManager);
    destroyEntityManager(&entityManager);
    destroyAudioManager(&audioManager);
    destroyFontManager(&fontManager);
    free_resource();
    quit();
    return;
}

void reset_game(){//重置游戏
    clear_old_entity();
    score = 0;
    live_time = -1;
    begin_time = time(NULL);
    player_alive = 1;
    audioManager.stopAll(&audioManager);
    paintManager.target.x = BACKGROUND_WIDTH / 2;
    paintManager.target.y = BACKGROUND_HEIGHT / 2;
    player = entityManager.create(&entityManager,PLAYER_WIDTH,PLAYER_HEIGHT,
    PLAYER,1,0,ANIMATIONS_SIZE,SPEED_PLAYER,BACKGROUND_WIDTH / 2,BACKGROUND_HEIGHT / 2,
    &update_player);
    entityManager.player = player;
    player->animations[RUN] = player_run_animation;
    player->animations[JUMP] = player_jump_animation;
    player->animations[CROUCH] = player_crouch_animation;
    player->currentAnim = player->animations[RUN];
    pre_player_pos = player->pos;
    pre_wall_pos.x = player->pos.x;
    pre_wall_pos.y = player->pos.y + 50;

    entity = entityManager.create(&entityManager,WALL_WIDTH,WALL_HEIGHT,WALL,1,1,ANIMATIONS_SIZE,0,
    pre_wall_pos.x,pre_wall_pos.y,&update_wall);
    entity->currentAnim = entity->animations[0] = wall_animations[0];

    if(back_time_ui){//释放旧数据
        back_time_ui->deleteLater = 1;
    }
    update_time_str(live_time + 1);//预加载0秒图片
    struct Texture *time_icon = fontManager.createTexture(&fontManager,WHITE,live_time_str,FONT_SIZE);
    int w = time_icon->w;
    int h = time_icon->h;
    back_time_ui = entityManager.create(&entityManager,w,h,UI,1,0,ANIMATIONS_SIZE,0,UI_TIME_X,UI_TIME_Y,&update_ui);
    back_time_ui->currentAnim = back_time_ui->animations[0] = newAnimation(w,h,1,1,0,time_icon);
    back_time_ui->visible = 0;    

    audioManager.playAudio(&audioManager,BGM,-1);

    for(int i = 0;i < BACKGROUND_SIZE;i++){
        background[i]->pos.x = BACKGROUND_WIDTH / 2.0;
        background[i]->pos.y = BACKGROUND_HEIGHT / 2.0;
    }
    update_score_ui();
    return;
}

void game_loop(){//游戏循环
    struct Point pos;
    while(1){
        if(close_window()){
            quit_game_flag = 1; 
            break;
        }
        inputManager.update();
        entityManager.updateAll(&entityManager);
        paintManager.target.x += 5.0;
        paintManager.paintAll(&paintManager);
        update_time_ui();
        if(player_alive){
            if(pre_wall_pos.x - player->pos.x < SUMMON_WALL_DIST_X){
                random_wall_summon();
            }
            if(onSkill){
                if(++skill_cnt == MAX_SKILL_CNT){
                    finish_skill();
                }else if(++summon_effect_1_cnt == MAX_SUMMON_EFFECT_1_CNT){
                    summon_effect_1_cnt = 0;
                    summon_effect_1();
                }
            }
            if(onHelicopter){
                helicopter_ui->pos.y -= 2;
                if(helicopter_ui->pos.y < MIN_HELICOPTER_Y){
                    leave_helicopter();
                }
            }
        }else{
            if(inputManager.buttonClicked(Button_Left,&pos)){
                if(click_button(pos.x,pos.y,UI_CONTINUE_ICON_X,UI_CONTINUE_ICON_Y,
                UI_CONTINUE_ICON_WIDTH / 2,UI_CONTINUE_ICON_HEIGHT / 2)){//继续游戏
                    continue_button->visible = 0;
                    quit_button->visible = 0;
                    reset_game();
                }else if(click_button(pos.x,pos.y,UI_QUIT_ICON_X,UI_QUIT_ICON_Y,
                UI_QUIT_ICON_WIDTH / 2,UI_QUIT_ICON_HEIGHT / 2)){//退出游戏
                    quit_game_flag = 1; 
                    break;
                }
            }
        }
        delay(16);
    }
    return;
}

void help_loop(){
    help_page->visible = !help_page->visible;
    inputManager.moveMouse(window,center_pos.x,center_pos.y);//移走鼠标，防止闪烁
    return;
}

void menu_loop(){
    paintManager.target.x = BACKGROUND_WIDTH / 2;
    paintManager.target.y = BACKGROUND_HEIGHT / 2;
    start_button->visible = 1;
    help_button->visible = 1;
    quit_button->visible = 1;
    title->visible = 1;
    struct Point pos;
    while(1){
        if(close_window()){
            quit_game_flag = 1; 
            break;
        }
        if(inputManager.buttonClicked(Button_Left,&pos)){
            if(click_button(pos.x,pos.y,UI_START_ICON_X,UI_START_ICON_Y,
            UI_START_ICON_WIDTH / 2,UI_START_ICON_HEIGHT / 2)){//开始游戏
                reset_game();
                break;

            }else if(click_button(pos.x,pos.y,UI_HELP_ICON_X,UI_HELP_ICON_Y,
            UI_HELP_ICON_WIDTH / 2,UI_HELP_ICON_HEIGHT / 2)){//游戏介绍
                help_loop();//其实就是显示一个图片，不退出菜单循环

            }else if(click_button(pos.x,pos.y,UI_QUIT_ICON_X,UI_QUIT_ICON_Y,
            UI_QUIT_ICON_WIDTH / 2,UI_QUIT_ICON_HEIGHT / 2)){//退出游戏
                quit_game_flag = 1; 
                break;
            }
        }
        inputManager.update();
        entityManager.updateAll(&entityManager);
        paintManager.target.x += 5.0;
        paintManager.paintAll(&paintManager);
        delay(16);
    }
    start_button->visible = 0;
    help_button->visible = 0;
    quit_button->visible = 0;
    help_page->visible = 0;
    title->visible = 0;
    return;
}

void game(){
    init_game();
    menu_loop();
    if(quit_game_flag){
        return;
    }
    game_loop();
    quit_game();
    return;
}

void gameOver(){
    player_alive = 0;
    continue_button->visible = 1;
    quit_button->visible = 1;
    audioManager.playAudio(&audioManager,CHUNK_DEATH,0);
    return;
}


int outOfScreen(struct Entity *entity){//掉出屏幕
    int dist_x = (int)paintManager.target.x - (int)entity->pos.x;
    int dist_y = (int)entity->pos.y - (int)paintManager.target.y;
    int max_dist_x = entity->w / 2 + SCREEN_WIDTH / 2;
    int max_dist_y = entity->h / 2 + SCREEN_HEIGHT / 2;
    return (dist_x > max_dist_x || dist_y > max_dist_y);
}

void getCollisionRect(struct Entity *entity,struct Rect *rect){//获取碰撞矩阵   
    int w = entity->w * entity->zoom_w;//碰撞体积
    int h = entity->h * entity->zoom_h;
    rect->x = (int)entity->pos.x - w / 2;
    rect->y = (int)entity->pos.y - h / 2;
    rect->w = w;
    rect->h = h;
    return;
} 

void updateFrame(struct Entity *entity,int zValue,int inWorld){//帧更新
    if(!entity || entity->deleteLater || !entity->visible) { return; }
    struct Animation *anim = entity->currentAnim;
    int row = anim->currentFrames / anim->cols;
    int col = anim->currentFrames % anim->cols;
    int w = anim->frame_w;
    int h = anim->frame_h;
    int x = w * col;
    int y = h * row;
    struct Point pos = {entity->pos.x - w / 2,entity->pos.y - h / 2};
    struct Rect rect = {x,y,w,h};
    struct PaintEvent event = {anim->spriteSheet,rect,pos,zValue,inWorld};
    paintManager.schedulePaint(&paintManager,&event);
    return;
}

void updateAnimation(struct Entity *entity){
    if (!entity || entity->deleteLater || !entity->currentAnim) { return; }
    struct Animation *anim = entity->currentAnim;
    if(++(anim->cnt) == MAX_ANIM_CNT){
        anim->cnt = 0;
        if(anim->currentFrames < anim->validFrames - 1){//继续播放
            anim->currentFrames++;
        }else if(anim->loop){//循环播放
            anim->currentFrames = 0;
        }
    }
    return;
}

void collision_wall(struct Entity *wall,struct Entity *other){//墙体碰撞,这里的墙指的是地板之类的
    if(!wall || !other || wall->deleteLater || other->deleteLater) { return; }
    struct Rect rect_wall,rect_other;
    getCollisionRect(wall,&rect_wall);
    getCollisionRect(other,&rect_other);
    if(!intersectRect(&rect_wall,&rect_other)) { return; }//不相交
    int left = rect_other.x + rect_other.w - rect_wall.x;
    int right = rect_wall.x + rect_wall.w - rect_other.x;
    int top = rect_other.y + rect_other.h - rect_wall.y;
    int bottom = rect_wall.y + rect_wall.h - rect_other.y;
    int min_intersect = min_int(min_int(left,right),min_int(top,bottom));
    if(left == min_intersect){
        other->pos.x -= left;
    }else if(right == min_intersect){
        other->pos.x += right;
    }else if(top == min_intersect){
        other->pos.y -= top;
    }else{
        other->pos.y += bottom;
    }
    return;
}

void attack(struct Entity *attacker,struct Entity *target){//攻击
    if(!attacker || !target || attacker->deleteLater || target->deleteLater) { return; }
    struct Rect rect_a,rect_t;
    getCollisionRect(attacker,&rect_a);
    getCollisionRect(target,&rect_t);
    if(intersectRect(&rect_a,&rect_t)){
        audioManager.playAudio(&audioManager,CHUNK_COLLISION,0);
        target->health -= attacker->attack;
    }
    return;
}

void cast_skill(){//释放技能
    onSkill = 1;
    skill_cnt = 0;
    player->attack = MAX_INT;
    player->health = MAX_INT;//技能期间无敌
    return;
}

void finish_skill(){//结束技能
    onSkill = 0;
    player->attack = 0;
    player->health = 1;
    return;
}

void ride_helicopter(){//掉虚空,若还有冰红茶,可以坐直升机上来
    if(onSkill){//坐直升机时停止技能
        finish_skill();
    }
    audioManager.playAudio(&audioManager,CHUNK_HELICOPTER,0);
    onHelicopter = 1;
    player->visible = 0;
    helicopter_ui->visible = 1;
    helicopter_ui->pos.x = SUMMON_HELICOPTER_X;
    helicopter_ui->pos.y = SUMMON_HELICOPTER_Y;
    return;
}

void leave_helicopter(){//离开直升机
    onHelicopter = 0;
    helicopter_ui->visible = 0;
    player->visible = 1;
    player->pos.x = helicopter_ui->pos.x - center_pos.x + paintManager.target.x;
    player->pos.y = helicopter_ui->pos.y - center_pos.y + paintManager.target.y;
    return;
}

void update_player_state(struct Entity *player){
    if(!player || player->deleteLater) { return; }
    if(player->pos.y - pre_player_pos.y < -LIMIT){//上升
        raising = 1;
        falling = 0;
    }else if(player->pos.y - pre_player_pos.y > LIMIT){//下降
        raising = 0;
        falling = 1;
    }else{//着陆
        onAir = 0;
        onWall = 1;
    }
    pre_player_pos = player->pos;
    return;
}

void playerControl(struct Entity *player){//玩家控制
    if(!player || player->deleteLater) { return; }
    update_player_state(player);
    if(inputManager.keyPressed(Key_Space)){
        if(tea_cnt > 0 && !onSkill){//还有
            tea_ui[--tea_cnt]->visible = 0;
            cast_skill();
        }
    }
    if(onWall){
        if(inputManager.keyPressed(Key_W)){
            jump_cnt = 0;
            onWall = 0;
            onAir = 1;
            player->zoom_w = JUMP_ZOOM_W;
            player->zoom_h = JUMP_ZOOM_H; 
            player->playAnimation(player,JUMP);
            audioManager.playAudio(&audioManager,CHUNK_JUMP,0);
        }else if(inputManager.keyPressed(Key_S)){
            player->zoom_w = CROUCH_ZOOM_W;
            player->zoom_h = CROUCH_ZOOM_H;
            player->playAnimation(player,CROUCH);
        }else{
            player->zoom_w = RUN_ZOOM_W;
            player->zoom_h = RUN_ZOOM_H;
            player->playAnimation(player,RUN);
        }
    }
    return;
}

void update_player(struct Entity *_this,struct EntityManager *manager){//玩家更新
    if(!_this || _this->deleteLater || onHelicopter) { return; }
    if(outOfScreen(_this)){
        if(tea_cnt > 0){//自动使用冰红茶
            tea_ui[--tea_cnt]->visible = 0;
            ride_helicopter();
        }else{
            _this->deleteLater = 1;
            gameOver();
            return;
        }
    }
    if(_this->health <= 0){
        if(tea_cnt > 0){//自动使用冰红茶
            tea_ui[--tea_cnt]->visible = 0;
            cast_skill();
        }else{
            _this->deleteLater = 1;
            gameOver();
            return;
        }
    }
    playerControl(_this);
    _this->pos.x += _this->speed;
    if(onAir && ++jump_cnt < MAX_JUMP_CNT){
        _this->pos.y -= GRAVITY;
    }else{
        _this->pos.y += GRAVITY;
    }
    struct Node_Entity *node;
    struct List_Entity *list = newList();
    /*墙体碰撞更新*/
    manager->getEntityByType(manager,list,WALL);
    node = list->head;
    for(int i = 0;i < list->size;i++,node = node->next){
        collision_wall(node->entity,_this);
    }
    clearList(list);
    /*攻击敌人*/
    manager->getEntityByType(manager,list,ENEMY);
    node = list->head;
    for(int i = 0;i < list->size;i++,node = node->next){
        attack(_this,node->entity);
    }
    clearListAndFree(list);
    /*动画更新*/
    updateAnimation(_this);
    updateFrame(_this,Z_PLAYER,IN_WORLD);
    return;
}

void update_effect(struct Entity *_this,struct EntityManager *manager){//特效更新
    if(!_this || _this->deleteLater) { return; }
    if(outOfScreen(_this)){
        _this->deleteLater = 1;
        return;
    }
    UNUSED(manager);//不用manager
    if(_this->currentAnim->currentFrames >= _this->currentAnim->validFrames - 1 && !_this->currentAnim->loop){
        _this->deleteLater = 1;
        return;
    }else{
        updateAnimation(_this);
    }
    updateFrame(_this,Z_EFFECT,IN_WORLD);
    return;
}

void update_enemy(struct Entity *_this,struct EntityManager *manager){//敌人更新
    if(!_this || _this->deleteLater) { return; }
    if(outOfScreen(_this) || _this->health <= 0){
        _this->deleteLater = 1;
        return;
    }
    attack(_this,manager->player);
    updateAnimation(_this);
    updateFrame(_this,Z_ENEMY,IN_WORLD);
    return;
}

void update_wall(struct Entity *_this,struct EntityManager *manager){//墙壁更新
    if(!_this || _this->deleteLater) { return; }
    if(outOfScreen(_this)){
        _this->deleteLater = 1;
        return;
    }
    updateAnimation(_this);
    updateFrame(_this,Z_WALL,IN_WORLD);
    return;
}

void update_item(struct Entity *_this,struct EntityManager *manager){//物品更新
    if(!_this || _this->deleteLater) { return; }
    if(outOfScreen(_this)){
        _this->deleteLater = 1;
        return;
    }
    struct Entity *player = manager->player;
    double dist_x = _this->pos.x - player->pos.x;
    double dist_y = _this->pos.y - player->pos.y;
    double dist = sqrt(pow(dist_x,2) + pow(dist_y,2));
    if(dist < _this->w / 2.0 + player->w / 2.0){//可以吃到
        audioManager.playAudio(&audioManager,CHUNK_COIN,0);
        score += ADD_SCORE;
        update_score_ui();
        if(_this->kind == TEA && tea_cnt < MAX_TEA_CNT){
            tea_ui[tea_cnt++]->visible = 1;
        }
        _this->deleteLater = 1;
        return;
    }
    updateAnimation(_this);
    updateFrame(_this,Z_ITEM,IN_WORLD);
    return;
}

void update_ui(struct Entity *_this,struct EntityManager *manager){//更新UI
    if(!_this || _this->deleteLater) { return; }
    updateAnimation(_this);
    updateFrame(_this,Z_UI,IN_SCREEN);
    return;
}

void update_background(struct Entity *_this,struct EntityManager *manager){//更新背景
    if(!_this || _this->deleteLater) { return; }
    UNUSED(manager);
    _this->pos.x += _this->speed;
    _this->currentAnim->currentFrames = 0;
    int dist = paintManager.target.x - _this->pos.x;
    if(dist > SCREEN_WIDTH / 2 + _this->w / 2 + 5){//越过循环交界处
        _this->pos.x += _this->w;
    }
    _this->pos.x += _this->w;
    updateFrame(_this,_this->zValue,IN_WORLD);
    _this->pos.x -= _this->w;
    updateFrame(_this,_this->zValue,IN_WORLD);
    return;
}


void summon_coin_line(double x,double y,int width){//生成一排金币
    int cnt = width / COIN_WIDTH / 2 + 1;//个数;
    struct Entity *coin = NULL;
    while(cnt--){
        coin = entityManager.create(&entityManager,COIN_WIDTH,COIN_HEIGHT,ITEM,1,0,ANIMATIONS_SIZE,
        0,x,y,&update_item);
        coin->currentAnim = coin->animations[0] = coin_animation;
        x += 2 * COIN_WIDTH;
    }
    return;
}

void random_enemy_1_summon(){//直升机
    double y = pre_wall_pos.y - WALL_HEIGHT / 2 - ENEMY_1_HEIGHT / 2 - PLAYER_WIDTH * CROUCH_ZOOM_H - 3;
    double x = rand() % (WALL_WIDTH / 4) - WALL_WIDTH / 8 + pre_wall_pos.x;
    struct Entity *entity = entityManager.create(&entityManager,ENEMY_1_WIDTH,ENEMY_1_HEIGHT,ENEMY,
    1,1,ANIMATIONS_SIZE,0,x,y,&update_enemy);
    entity->currentAnim = entity->animations[0] = enemy_animations[0];
    summon_coin_line(x - ENEMY_1_WIDTH / 2,pre_wall_pos.y - WALL_HEIGHT,ENEMY_1_WIDTH);
    return;
}

void random_enemy_2_summon(){//石头
    double y = pre_wall_pos.y - WALL_HEIGHT / 2 - ENEMY_2_HEIGHT / 2;
    double x = rand() % (WALL_WIDTH / 4) - WALL_WIDTH / 8 + pre_wall_pos.x;
    struct Entity *entity = entityManager.create(&entityManager,ENEMY_2_WIDTH,ENEMY_2_HEIGHT,ENEMY,
    1,1,ANIMATIONS_SIZE,0,x,y,&update_enemy);
    entity->currentAnim = entity->animations[0] = enemy_animations[1];
    summon_coin_line(x - ENEMY_2_WIDTH / 2,y - JUMP_HEIGHT,ENEMY_2_WIDTH);
    return;
}


void random_enemy_3_summon(){//枯木
    double y = pre_wall_pos.y - WALL_HEIGHT / 2 - ENEMY_3_HEIGHT / 2;
    double x = rand() % (WALL_WIDTH / 4) - WALL_WIDTH / 8 + pre_wall_pos.x;
    entity = entityManager.create(&entityManager,ENEMY_3_WIDTH,ENEMY_3_HEIGHT,ENEMY,
    1,1,ANIMATIONS_SIZE,0,x,y,&update_enemy);
    entity->currentAnim = entity->animations[0] = enemy_animations[2];
    summon_coin_line(x - ENEMY_3_WIDTH / 2,y - JUMP_HEIGHT,ENEMY_3_WIDTH);
    return;
}

void random_wall_summon(){//随机墙壁生成,顺带在墙上生成静态障碍物
    int y_up = (pre_wall_pos.y - MIN_SUMMON_Y) * 0.9;//保险起见乘以0.9
    int y_down = (MAX_SUMMON_Y - pre_wall_pos.y) * 0.9;
    double y = rand() % (y_up + y_down) - y_up;
    pre_wall_pos.x += ADD_WALL_POS_X;
    pre_wall_pos.y += max_double(y,-JUMP_HEIGHT);
    struct Entity *entity = entityManager.create(&entityManager,WALL_WIDTH,WALL_HEIGHT,WALL,1,1,BUFFER_SIZE,0,
    pre_wall_pos.x,pre_wall_pos.y,&update_wall);
    entity->currentAnim = entity->animations[0] = wall_animations[0];
    if(rand() % TEA_SUMMON_RATIO == 0){//生成冰红茶
        entity = entityManager.create(&entityManager,TEA_WIDTH,TEA_HEIGHT,ITEM,1,0,ANIMATIONS_SIZE,0,
        pre_wall_pos.x,pre_wall_pos.y - PLAYER_HEIGHT * 2,&update_item);
        entity->currentAnim = entity->animations[0] = tea_animation;
        entity->kind = TEA;
    }else{
        switch(rand() % 3){
            case 0: random_enemy_1_summon();break;
            case 1: random_enemy_2_summon();break;
            case 2: random_enemy_3_summon();break;
        }
    }

    return;
}

void summon_effect_1(){
    struct Entity *effect = entityManager.create(&entityManager,EFFECT_1_WIDTH,EFFECT_1_HEIGHT,EFFECT,
    1,0,ANIMATIONS_SIZE,0,player->pos.x,player->pos.y,&update_effect);
    effect->currentAnim = effect->animations[0] =
    newAnimation(EFFECT_1_WIDTH,EFFECT_1_HEIGHT,24,0,0,effect_1_texture);
    return;
}


#endif