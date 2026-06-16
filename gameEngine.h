#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include <SDL.h>//SDL库文件
#include <SDL_image.h>//SDL库文件
#include <SDL_mixer.h>//SDL库文件
#include <SDL_ttf.h>//SDL库文件
#include <stdlib.h>//rand函数

#define UNUSED(x) ((void)(x))//不使用变量

struct Window;
struct Point;
struct Animation;
struct PaintEvent;
struct PaintManager;
struct Node_Entity;
struct List_Entity;
struct Entity;
struct EntityManager;
struct Audio;
struct AudioManager;
struct FontManager;
struct Color;

void playAnimation(struct Entity *_this,int index);//播放动画
void stopAnimation(struct Entity *_this);//停止动画
void schedulePaint(struct PaintManager *_this,struct PaintEvent *event);//准备绘制
void paintAll(struct PaintManager *_this);//绘制
void insertNode(struct List_Entity *_this,struct Node_Entity *node);
void deleteThisNode(struct List_Entity *_this,struct Node_Entity *node);//删除指定节点
void removeThisNode(struct List_Entity *_this,struct Node_Entity *node);//移除指定节点
void updateAll(struct EntityManager *_this);//更新所有实体
struct Entity *createEntity
(struct EntityManager *_this,int w,int h,int type,int hp,
int attack,int bufferSize,double speed,double x,double y,
void (*update)(struct Entity *_this,struct EntityManager *manager));//创建实体
void getEntityByType(struct EntityManager *_this,struct List_Entity *list,int type);//按类型获取实体
void addAudio(struct AudioManager *_this,char path[],int index,int isMusic);//添加音频
void playAudio(struct AudioManager *_this,int index,int loops);//播放音频
void stopAll(struct AudioManager *_this);//停止播放
int keyPressed(int val);//按键检测
int buttonClicked(int val,struct Point *pos);//鼠标检测
struct Texture* createTexture(struct FontManager *_this,struct Color color,char text[],int fontSize);//创建字体纹理
void moveMouse(struct Window *window,int x,int y);//移动鼠标

int max_int(int a,int b){
    return a > b ? a : b;
}

int max_double(double a,double b){
    return a > b ? a : b;
}

int min_int(int a,int b){
    return a > b ? b : a;
}

int min_double(double a,double b){
    return a > b ? b : a;
}

struct Point{
    int x;
    int y;
};

struct PointF{
    double x;
    double y;
};

struct Rect{
    int x;
    int y;
    int w;
    int h;
};

int intersectRect(struct Rect *rect1,struct Rect *rect2){//判断矩形是否相交
    if(rect1->x >= rect2->x + rect2->w
    || rect1->x + rect1->w <= rect2->x
    || rect1->y >= rect2->y + rect2->h
    || rect1->y + rect1->h <= rect2->y){
        return 0;
    }
    return 1;
}

struct RectF{
    double x;
    double y;
    double w;
    double h;
};

void initEngine(){//初始化引擎
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    return;
}

int close_window(){//关闭窗口
    SDL_Event event;
    int flag = 0;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            flag = 1;
        }
    }
    return flag;
}

void delay(uint32_t ms){
    SDL_Delay(ms);
    return;
}

void quit(){
    SDL_Quit();
    return;
}

struct Window{
    SDL_Window *m_window;
};

struct Window *newWindow(char title[],int w,int h){
    struct Window *window = (struct Window*)malloc(sizeof(struct Window));
    SDL_Window *m_window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,SDL_WINDOW_SHOWN);
    window->m_window = m_window;
    return window;
}

void deleteWindow(struct Window *window){
    if(window == NULL) { return; }
    SDL_DestroyWindow(window->m_window);
    free(window);
    return;
}

struct Renderer{
    SDL_Renderer *m_renderer;
};

struct Renderer *newRenderer(struct Window *window){
    struct Renderer *renderer = (struct Renderer*)malloc(sizeof(struct Renderer));
    SDL_Renderer *m_renderer = SDL_CreateRenderer(window->m_window,-1,SDL_RENDERER_ACCELERATED);
    renderer->m_renderer = m_renderer;
    return renderer;
}

void deleteRenderer(struct Renderer *renderer){
    if(renderer == NULL) { return; }
    SDL_DestroyRenderer(renderer->m_renderer);
    free(renderer);
    return;
}

struct Surface{//内存表面
    int w;
    int h;
    int shared;//是否共享
    SDL_Surface *m_surface;
};

struct Surface *newSurface(char path[],int shared){
    struct Surface *surface = (struct Surface*)malloc(sizeof(struct Surface));
    SDL_Surface *m_surface = IMG_Load(path);
    surface->w = m_surface->w;
    surface->h = m_surface->h;
    surface->m_surface = m_surface;
    surface->shared = shared;
    return surface;
}

void deleteSurface(struct Surface *surface){
    if(surface == NULL) { return; }
    SDL_FreeSurface(surface->m_surface);
    free(surface);
    return;
}

struct Texture{//显存纹理
    int w;
    int h;
    int shared;
    SDL_Texture *m_texture;
};

struct Texture *newTexture(struct Renderer *renderer,char path[],int shared){
    int w,h;
    struct Texture *texture = (struct Texture*)malloc(sizeof(struct Texture));
    SDL_Texture *m_texture = IMG_LoadTexture(renderer->m_renderer,path);
    SDL_QueryTexture(m_texture,NULL,NULL,&w,&h);
    texture->m_texture = m_texture;
    texture->w = w;
    texture->h = h;
    texture->shared = shared;
    return texture;    
}

void deleteTexture(struct Texture *texture){
    if(texture == NULL) { return; }
    SDL_DestroyTexture(texture->m_texture);
    free(texture);
    return;
}

struct Animation{//动画
    int cnt;//计数器
    int rows;//子图行数
    int cols;
    int frame_w;
    int frame_h;
    int validFrames;//总帧数
    int currentFrames;
    int loop;//是否循环播放
    int shared;
    struct Texture *spriteSheet;//精灵图
};

struct Animation *newAnimation(int w,int h,int vf,int loop,int shared,struct Texture *sheet){
    struct Animation *anim = (struct Animation*)malloc(sizeof(struct Animation));
    anim->cnt = 0;
    anim->rows = sheet->h / h;
    anim->cols = sheet->w / w;
    anim->frame_w = w;
    anim->frame_h = h;
    anim->validFrames = vf;
    anim->currentFrames = -1;
    anim->loop = loop;
    anim->spriteSheet = sheet;
    anim->shared = shared;
    return anim;
}

void deleteAnimation(struct Animation *anim){
    if(anim == NULL) { return; }
    if(!anim->spriteSheet->shared){//精灵图无共享
        deleteTexture(anim->spriteSheet);
    }
    free(anim);
    return;
}

struct PaintEvent{//绘图事件
    struct Texture *texture;
    struct Rect rect;//绘制范围
    struct Point pos;//左上角点
    int zValue;//z轴坐标
    int inWorld;//0表示屏幕坐标，1表示世界坐标
};

struct PaintManager{//绘图管理器
    int size;
    int bufferSize;//缓冲区大小
    int *help;//辅助数组
    struct PointF target;//焦点
    struct Point screen_center;//窗口中心点
    struct PaintEvent *queue;//事件队列
    struct Renderer *renderer;
    void (*schedulePaint)(struct PaintManager *_this,struct PaintEvent *event);
    void (*paintAll)(struct PaintManager *_this);
};

void paint(struct PaintManager *manager,struct PaintEvent *event){//绘制
    int x,y,w,h;
    w = event->rect.w;
    h = event->rect.h;
    if(event->inWorld){//世界坐标
        x = event->pos.x - (int)manager->target.x + manager->screen_center.x;
        y = event->pos.y - (int)manager->target.y + manager->screen_center.y;
    }else{//屏幕坐标
        x = event->pos.x;
        y = event->pos.y;
    }
    SDL_Rect srect = {event->rect.x,event->rect.y,w,h};
    SDL_Rect drect = {x,y,w,h};
    SDL_RenderCopy(manager->renderer->m_renderer,event->texture->m_texture,&srect,&drect);
    return;
}

void initPaintManager(struct PaintManager *manager,struct Point center,struct Renderer *renderer,int bufferSize){//初始化
    static int flag = 1;
    if(!flag) { return; }//禁止创建多个管理器
    flag = 0;
    manager->size = 0;
    manager->bufferSize = bufferSize;
    manager->help = (int*)malloc(sizeof(int) * bufferSize);
    manager->screen_center = center;
    manager->queue = (struct PaintEvent*)malloc(sizeof(struct PaintEvent) * bufferSize);
    manager->renderer = renderer;
    manager->schedulePaint = &schedulePaint;
    manager->paintAll = &paintAll;
    return;
}

void destroyPaintManager(struct PaintManager *manager){
    if(manager == NULL) { return; }
    free(manager->help);
    free(manager->queue);
    free(manager);
    return;
}

struct Entity{//实体
    int w;
    int h;
    int id;
    int type;//粗分(player,enemy等)
    int kind;//细分(enemy_a,enemy_b等)
    int zValue;
    int health;
    int attack;
    int visible;//能否看见
    int bufferSize;
    int deleteLater;//延迟删除
    double speed;
    double zoom_w;//缩放率
    double zoom_h;
    struct PointF pos;
    struct Animation **animations;
    struct Animation *currentAnim;
    void (*update)(struct Entity *_this,struct EntityManager *manager);
    void (*playAnimation)(struct Entity *_this,int index);
    void (*stopAnimation)(struct Entity *_this);
};

struct Entity *newEntity
(
    int w,int h,int id,int type,int hp,int attack,int bufferSize,double speed,double x,double y,
    void (*update)(struct Entity *_this,struct EntityManager *manager)
)
{
    struct Entity *entity = (struct Entity*)malloc(sizeof(struct Entity));
    entity->w = w;
    entity->h = h;
    entity->id = id;
    entity->type = type;
    entity->kind = -1;
    entity->health = hp;
    entity->attack = attack;
    entity->visible = 1;
    entity->bufferSize = bufferSize;
    entity->deleteLater = 0;
    entity->speed = speed;
    entity->zoom_w = entity->zoom_h = 1.0;
    entity->pos.x = x;
    entity->pos.y = y;
    entity->animations = (struct Animation**)malloc(sizeof(struct Animation*) * bufferSize);
    entity->currentAnim = NULL;
    entity->update = update;
    entity->playAnimation = &playAnimation;
    entity->stopAnimation = &stopAnimation;
    for(int i = 0;i < bufferSize;i++){
        entity->animations[i] = NULL;
    }
    return entity;
}

void deleteEntity(struct Entity *entity){
    if(entity == NULL) { return; }
    for(int i = 0;i < entity->bufferSize;i++){
        if(entity->animations[i] && !entity->animations[i]->shared){//非共享
            deleteAnimation(entity->animations[i]);
        }
    }
    free(entity->animations);
    free(entity);
    return;
}

struct Node_Entity{//实体节点
    struct Entity *entity;
    struct Node_Entity* pre;
    struct Node_Entity* next;
};

struct List_Entity{//实体链表
    int size;
    struct Node_Entity *head;
    struct Node_Entity *tail;
    void (*insert)(struct List_Entity *_this,struct Node_Entity *node);//插入
    void (*deleteThisNode)(struct List_Entity *_this,struct Node_Entity *node);//删除指定节点
    void (*removeThisNode)(struct List_Entity *_this,struct Node_Entity *node);//移除指定节点
};

struct Node_Entity *newNode(struct Entity *entity){
    struct Node_Entity *node = (struct Node_Entity*)malloc(sizeof(struct Node_Entity));
    node->next = node->pre = NULL;
    node->entity = entity;
    return node;
}

struct List_Entity *newList(){
    struct List_Entity *list = (struct List_Entity*)malloc(sizeof(struct List_Entity));
    list->size = 0;
    list->head = list->tail = NULL;
    list->insert = &insertNode;
    list->deleteThisNode = &deleteThisNode;
    list->removeThisNode = &removeThisNode;
    return list;
}

void deleteNode(struct Node_Entity *node){
    if(node == NULL) { return; }
    deleteEntity(node->entity);    
    free(node);
    return;
}

void insertNode(struct List_Entity *_this,struct Node_Entity *node){
    struct Node_Entity *cur = newNode(node->entity);//深拷贝!!!,我花了2h才找到BUG!!!
    if(_this->size == 0){
        _this->head = _this->tail = cur;
    }else{
        cur->pre = _this->tail;
        _this->tail->next = cur;
        _this->tail = cur;
    }
    _this->size++;
    return;
}

void removeThisNode(struct List_Entity *_this,struct Node_Entity *node){
    if(_this->head == node){
        _this->head = _this->head->next;
    }else if(_this->tail == node){
        _this->tail = _this->tail->pre;
    }else{
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }
    _this->size--;
    return;
}

void deleteThisNode(struct List_Entity *_this,struct Node_Entity *node){
    removeThisNode(_this,node);
    deleteNode(node);
    return;
}

void clearList(struct List_Entity *list){
    if(!list) { return; }
    struct Node_Entity *cur = list->head;
    struct Node_Entity *tail = list->tail;
    while(cur != tail){
        cur = cur->next;
        free(cur->pre);
    } 
    free(cur);
    list->head = list->tail = NULL;
    list->size = 0;
    return;
}

void clearListAndFree(struct List_Entity *list){
    if(!list) { return; }
    clearList(list);
    free(list);
    return;
}

void deleteList(struct List_Entity *list){
    if(list == NULL) { return; }
    if(list->size){
        struct Node_Entity *cur = list->head;
        while(cur != list->tail){
            cur = cur->next;
            deleteNode(cur->pre);
        }
        deleteNode(list->tail);
    }
    free(list);
    return;
}

struct EntityManager{//实体管理机
    int id_cnt;//id计数器
    struct Entity *player;//玩家
    struct List_Entity *list_entity;//所有实体链表
    void (*updateAll)(struct EntityManager *_this);
    struct Entity* (*create)
    (struct EntityManager *_this,int w,int h,int type,int hp,
    int attack,int bufferSize,double speed,double x,double y,
    void (*update)(struct Entity *_this,struct EntityManager *manager));
    void (*getEntityByType)(struct EntityManager *_this,struct List_Entity *list,int type);
};

void initEntityManager(struct EntityManager *manager){
    static int flag = 1;
    if(!flag) { return; }//只构造一次
    flag = 0;
    manager->id_cnt = 0;
    manager->player = NULL;
    manager->list_entity = newList();
    manager->updateAll = &updateAll;
    manager->create = &createEntity;
    manager->getEntityByType = &getEntityByType;
    return;
}

void destroyEntityManager(struct EntityManager *manager){
    if(manager == NULL) { return; }
    deleteList(manager->list_entity);
    free(manager);
    return;
}

struct Audio{//音频
    Mix_Music *music;
    Mix_Chunk *chunk;
    int isMusic;//标记音频类型
};

struct Audio *newAudio(char path[],int isMusic){
    struct Audio *audio = (struct Audio*)malloc(sizeof(struct Audio));
    audio->isMusic = isMusic;
    if(isMusic){
        audio->music = Mix_LoadMUS(path);
    }else{
        audio->chunk = Mix_LoadWAV(path);
    }
    return audio;
}

void deleteAudio(struct Audio *audio){
    if(audio == NULL) { return; }
    if(audio->isMusic){
        Mix_FreeMusic(audio->music);
    }else{
        Mix_FreeChunk(audio->chunk);
    }
    free(audio);
    return;
}

struct AudioManager{//音频管理机
    int bufferSize;
    struct Audio **audios;
    void (*addAudio)(struct AudioManager *_this,char path[],int index,int isMusic);
    void (*playAudio)(struct AudioManager *_this,int index,int loops);
    void (*stopAll)(struct AudioManager *_this);
};

void initAudioManager(struct AudioManager *manager,int bufferSize,int channels){
    static int flag = 1;
    if(!flag) { return; }
    flag = 0;
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    Mix_AllocateChannels(channels);
    manager->bufferSize = bufferSize;
    manager->audios = (struct Audio**)malloc(sizeof(struct Audio*) * bufferSize);
    manager->addAudio = &addAudio;
    manager->playAudio = &playAudio;
    manager->stopAll = &stopAll;
    for(int i = 0;i < bufferSize;i++){
        manager->audios[i] = NULL;
    }
    return;
}

void destroyAudioManager(struct AudioManager *manager){
    if(manager == NULL) { return; }
    for(int i = 0;i < manager->bufferSize;i++){
        if(manager->audios[i]){
            deleteAudio(manager->audios[i]);
        }
    }
    free(manager->audios);
    free(manager);
    return;
}

enum Key{
    Key_W = SDL_SCANCODE_W,
    Key_A = SDL_SCANCODE_A,
    Key_S = SDL_SCANCODE_S,
    Key_D = SDL_SCANCODE_D,
    Key_J = SDL_SCANCODE_J,
    Key_K = SDL_SCANCODE_K,
    Key_L = SDL_SCANCODE_L,
    Key_Space = SDL_SCANCODE_SPACE
};

enum Button{
    Button_Left = SDL_BUTTON_LEFT,
    Button_Right = SDL_BUTTON_RIGHT,
    Button_Middle = SDL_BUTTON_MIDDLE
};

struct InputManager{//输入管理器
    void (*update)();
    void (*moveMouse)(struct Window *window,int x,int y);
    int (*keyPressed)(int val);
    int (*buttonClicked)(int val,struct Point *pos);
};

void initInputManager(struct InputManager *manager){
    static int flag = 1;
    if(!flag) { return; }
    flag = 0;
    manager->update = &SDL_PumpEvents;
    manager->moveMouse = &moveMouse;
    manager->keyPressed = &keyPressed;
    manager->buttonClicked = &buttonClicked;
    return;
}

struct Color{//颜色
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct FontManager{//字体管理器
    const char* path;//ttf文件地址
    int bufferSize;
    TTF_Font **fonts;
    struct Renderer *renderer;
    struct Texture* (*createTexture)(struct FontManager *_this,struct Color color,char text[],int fontSize);
};

void initFontManager(struct FontManager *manager,struct Renderer *renderer,int bufferSize,char path[]){
    static int flag = 1;
    if(!flag) { return; }
    flag = 0;
    TTF_Init();
    manager->path = path;
    manager->bufferSize = bufferSize;
    manager->fonts = (TTF_Font**)malloc(sizeof(TTF_Font*) * bufferSize);
    manager->renderer = renderer;
    manager->createTexture = &createTexture;
    for(int i = 0;i < bufferSize;i++){
        manager->fonts[i] = NULL;
    }
    return;
}

void destroyFontManager(struct FontManager *manager){
    if(manager == NULL) { return; }
    for(int i = 0;i < manager->bufferSize;i++){
        if(manager->fonts[i]){
            TTF_CloseFont(manager->fonts[i]);
        }
    }
    free(manager->fonts);
    free(manager);
    TTF_Quit();
}


/*结构体内方法*/

void playAnimation(struct Entity *_this,int index){
    if(_this->currentAnim != _this->animations[index]){//不同动画
        _this->currentAnim = _this->animations[index];
        _this->currentAnim->currentFrames = 0;
    }
    return;
}

void stopAnimation(struct Entity *_this){
    _this->currentAnim = NULL;
    return;
}

void schedulePaint(struct PaintManager *_this,struct PaintEvent *event){
    if(_this->size < _this->bufferSize){
        _this->queue[_this->size++] = *event;
    }
    return;
}

void paintAll(struct PaintManager *_this){
    int size = _this->size;
    int *pointer = _this->help;
    for(int i = 0;i < size;i++){
        pointer[i] = i;
    }
    for(int i = 0;i < size;i++){//zValue排序
        for(int j = size - 1;j > i;j--){
            if(_this->queue[pointer[j]].zValue < _this->queue[pointer[j - 1]].zValue){
                int tmp = pointer[j];
                pointer[j] = pointer[j - 1];
                pointer[j - 1] = tmp;
            }
        }
    }
    for(int i = 0;i < size;i++){
        paint(_this,&_this->queue[pointer[i]]);
    }
    SDL_RenderPresent(_this->renderer->m_renderer);
    _this->size = 0;
    return;
}

void updateAll(struct EntityManager *_this){
    struct Node_Entity *cur = _this->list_entity->head;
    struct Node_Entity *tail = _this->list_entity->tail;
    while(cur != tail){
        if(cur->entity->deleteLater){//删除
            cur = cur->next;
            _this->list_entity->deleteThisNode(_this->list_entity,cur->pre);
        }else{
            cur->entity->update(cur->entity,_this);
            cur = cur->next;
        }
    }
    if(cur->entity->deleteLater){
        _this->list_entity->deleteThisNode(_this->list_entity,cur);
    }else{
        cur->entity->update(cur->entity,_this);
    }
    return;
}

struct Entity *createEntity
(struct EntityManager *_this,int w,int h,int type,int hp,
int attack,int bufferSize,double speed,double x,double y,
void (*update)(struct Entity *_this,struct EntityManager *manager)){
    int id = _this->id_cnt++;
    struct Entity *entity = newEntity(w,h,id,type,hp,attack,bufferSize,speed,x,y,update);
    struct Node_Entity *node = newNode(entity);
    _this->list_entity->insert(_this->list_entity,node);
    return entity;
}

void getEntityByType(struct EntityManager *_this,struct List_Entity *list,int type){
    struct Node_Entity *cur = _this->list_entity->head;
    struct Node_Entity *tail = _this->list_entity->tail;
    while(cur != tail){
        if(!cur->entity->deleteLater && cur->entity->type == type){
            list->insert(list,cur);
        }
        cur = cur->next;
    }
    if(!cur->entity->deleteLater && cur->entity->type == type){
        list->insert(list,cur);
    }
    return;
}

void addAudio(struct AudioManager *_this,char path[],int index,int isMusic){
    struct Audio *audio = newAudio(path,isMusic);
    _this->audios[index] = audio;
    return;
}

void playAudio(struct AudioManager *_this,int index,int loops){
    if(_this->audios[index]->isMusic){
        Mix_PlayMusic(_this->audios[index]->music,loops);
    }else{
        Mix_PlayChannel(-1,_this->audios[index]->chunk,loops);
    }
    return;
}

void stopAll(struct AudioManager *_this){
    UNUSED(_this);
    Mix_HaltMusic();
    Mix_HaltChannel(-1);
    return;
}

int keyPressed(int val){
    const uint8_t* keys = SDL_GetKeyboardState(NULL);
    if(keys[val]){
        return 1;
    }
    return 0;
    
}

int buttonClicked(int val,struct Point *pos){
    uint32_t buttons = SDL_GetMouseState(&pos->x,&pos->y);
    return buttons & SDL_BUTTON(val);
}

void moveMouse(struct Window *window,int x,int y){
    SDL_WarpMouseInWindow(window->m_window,x,y);
    return;
}

struct Texture* createTexture(struct FontManager *_this,struct Color color,char text[],int fontSize){
    if(!_this->fonts[fontSize]){
        _this->fonts[fontSize] = TTF_OpenFont(_this->path,fontSize);
    }
    int w,h;
    SDL_Color sdl_color = {color.r,color.g,color.b,color.a};
    SDL_Surface *surface = TTF_RenderUTF8_Blended(_this->fonts[fontSize],text,sdl_color);
    SDL_Texture *m_texture = SDL_CreateTextureFromSurface(_this->renderer->m_renderer,surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(m_texture,NULL,NULL,&w,&h);
    struct Texture *texture = (struct Texture*)malloc(sizeof(struct Texture));
    texture->w = w;
    texture->h = h;
    texture->m_texture = m_texture;
    texture->shared = 0;
    return texture;
}


#endif