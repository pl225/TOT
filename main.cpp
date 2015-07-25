#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

#define FPS 12

int jogoRodando = 1, teclaDireita = 0, teclaEsquerda = 0, teclaCima=0, teclaBaixo=0, teclaEspaco=0, time=0, frame=0, pulo=0, jump=0;
int p_cima=0, p_baixo=0, subindo=0, toques=0, toques_1=0, toques_2=0, toques_3=0;
int score=0, lifes=4, pontuacao_final=0, bdireita=0, besquerda=0, fds=0, frame_sword=0, c_espada=0, frame_voldemort=0;
float tam_pulo=0;
int bateu=0, bateu1=0, bateu2=0, bateu3=0, bateu4=0;
int marcar=0, marcar1=0, marcar2=0, marcar3=0, marcar4=0;
// Variaveis de Movimento das fireball
 int direita=0, baixo=0, esquerda=0, direita1=0, baixo1=0, esquerda1=0,
     direita2=0, baixo2=0, esquerda2=0, direita3=0, baixo3=0, esquerda3=0,
     direita4=0, baixo4=0, esquerda4=0;
//fireballs
int fr=1;
//fogo
typedef struct FOGO Fogo;
struct FOGO
{
     float sx, sy, dx, dy;
};

Fogo fogo;
Fogo fogo_1;
Fogo fogo_2;
Fogo fogo_3;
Fogo fogo_4;

SDL_Surface *playerImage = NULL;
SDL_Surface *player_subir = NULL;
SDL_Surface *player_sword = NULL;
SDL_Surface *background = NULL;
SDL_Surface *Recorde = NULL;
SDL_Surface *Creditos = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *plataforma = NULL;
SDL_Surface *escada = NULL;
SDL_Surface *gold = NULL;
SDL_Surface *plataforma_pequena = NULL;
SDL_Surface *voldemort_s = NULL;
SDL_Surface *Gina_s = NULL;
SDL_Surface *fireball = NULL;
SDL_Surface *escada_quebrada = NULL;
SDL_Surface *Controles = NULL;
SDL_Surface *plataforma_menor = NULL;
SDL_Surface *menu = NULL;
SDL_Surface *game_over = NULL;
SDL_Surface *ganhou = NULL;
SDL_Surface *perdeu_vida = NULL;
SDL_Surface *pontos = NULL;
SDL_Surface *score_ = NULL;
SDL_Surface *vidas = NULL;
SDL_Surface *vidas_ = NULL;
SDL_Surface *tempo_restante = NULL;
SDL_Surface *tempo_espada = NULL;
SDL_Surface *minutos = NULL;
SDL_Surface *segundos = NULL;
SDL_Surface *Espada = NULL;
SDL_Surface *Pergaminho = NULL;

Mix_Music *musica = NULL;
Mix_Music *principal = NULL;
Mix_Chunk *colisao = NULL;

TTF_Font *t_1 = NULL;
SDL_Color textColor = { 0, 0, 0 };

SDL_Event event;
Uint32 start;
Uint32 t_restante;
Uint32 iniciou;
Uint32 t_restou;
Uint32 t_espada;
Uint32 zzz;
Uint32 ttt;
SDL_Rect v[4];
SDL_Rect voldemort[4];
SDL_Rect Gina[4];
SDL_Rect snake;
SDL_Rect sword[2];

//fireball
SDL_Rect f;
SDL_Rect f1;
SDL_Rect f2;
SDL_Rect f3;
SDL_Rect f4;
//pomos de ouro
SDL_Rect g;
SDL_Rect g_1;
SDL_Rect g_2;
SDL_Rect g_3;
//botoes dos menus
SDL_Rect butao;
SDL_Rect sim;
SDL_Rect voltar;
SDL_Rect rec_1;
SDL_Rect creditos;
SDL_Rect controles;
SDL_Rect nao;
SDL_Rect tentar;
//personagem
SDL_Rect personagem;
//fontes
SDL_Rect fontes;
//plataformas
SDL_Rect p;
SDL_Rect p_1;
SDL_Rect p_2;
SDL_Rect p_3;
SDL_Rect p_4;
SDL_Rect p_5;
//espadas
SDL_Rect esp_sword;

void draw_player(float srcX, float srcY, float dstX, float dstY, int width, int height, SDL_Surface* source, SDL_Surface* destination)
{
   SDL_Rect sourc, destino;
   sourc.x = srcX;
   sourc.y = srcY;
   sourc.w = width;
   sourc.h = height;

   destino.x = dstX;
   destino.y = dstY;
   destino.w = width;
   destino.h = height;

   SDL_BlitSurface(source, &sourc, destination, &destino);
}

typedef struct PLAYER Player;
struct PLAYER
{
     float sx, sy, dx, dy, velx, vely, up, sxesp;
     int largura, altura, pulo, larguraesp;
};

Player player;


void playerInfo()
{
    player.largura = 60, player.altura = 60, player.pulo = 3, player.larguraesp=70, player.sxesp=0;
	player.sx =0, player.sy = 0, player.dx =0, player.dy = 520, player.velx = 4.5, player.vely =5.5;
	player.up=0, subindo=0, jump=0, pulo=0, p_cima=0, p_baixo=0;
	playerImage = IMG_Load("player.png");
	/*fogo.sx=0, fogo.sy=0, fogo_1.sx=0, fogo_1.sy=0, fogo_2.sx=0, fogo_2.sy=0, fogo_3.sx=0, fogo_3.sy=0;
	fogo_4.sx=0, fogo_4.sy=0;
	direita=0, baixo=0, esquerda=0, direita1=0, baixo1=0, esquerda1=0, direita2=0, baixo2=0, esquerda2=0,
	direita3=0, baixo3=0, esquerda3=0, direita4=0, baixo4=0, esquerda4=0;*/
	//toques=0, toques_1=0, toques_2=0, toques_3=0;
}

void carregaArquivos()
{
   	playerImage = IMG_Load("player.png");
   	Espada = IMG_Load("sword.png");
   	player_sword = IMG_Load("harryd.png");
   	player_subir = IMG_Load("subir_1.png");
	background = IMG_Load("background(1).png");
	plataforma = IMG_Load("plataforma (2).png");
	escada = IMG_Load("escada_nova.png");
	escada_quebrada = IMG_Load("escada_quebrada.png");
	Creditos = IMG_Load("creditos.jpg");
	gold = IMG_Load("gold.png");
	Controles = IMG_Load("controles prontos.jpg");
	Recorde = IMG_Load("recordes pronto.jpg");
	screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
	SDL_WM_SetCaption( "Tales of Tales", NULL );
	plataforma_pequena = IMG_Load("plataforma_pequena.png");
	voldemort_s = IMG_Load("voder_n.png");
	Gina_s = IMG_Load("gina.png");
	fireball = IMG_Load("fire_30.png");
	plataforma_menor = IMG_Load("plataforma_menor.png");
	menu = IMG_Load("menu pronto.jpg");
	game_over = IMG_Load("Game Over.jpg");
	musica = Mix_LoadMUS("Spirit Of The Radio.wav");
	principal = Mix_LoadMUS("Spiders and Vinegaroons.wav");
	colisao = Mix_LoadWAV("colisao.wav");
	t_1 = TTF_OpenFont("harryp.TTF", 30);
	perdeu_vida = IMG_Load("perde_vida.jpg");
	ganhou = IMG_Load("vc_e_bom.jpg");
	Pergaminho = IMG_Load("pergaminho.png");
}

bool check_collision( SDL_Rect A, SDL_Rect B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB + 15)
    {
        return false;
    }

    if( topA + 15>= bottomB)
    {
        return false;
    }

    if( rightA <= leftB + 15)
    {
        return false;
    }

    if( leftA  + 15>= rightB)
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

void inicializa()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
	TTF_Init();
	playerInfo();
	carregaArquivos();
}

void andar()
{
	 if(teclaDireita)
    {
        bdireita=1;
        besquerda=0;
        if ((player.dx>=0 && player.dy>518 && player.dy<522)/*|| !(player.dy>268 && player.dy<355 && player.dx>195 && player.dx<212)*/) {
            SDL_Surface *aux = playerImage;
            if (c_espada==0) {
                playerImage = IMG_Load("player.png");
                SDL_FreeSurface(aux);
                if (player.dx>=669) {
                    player.sx += player.largura;
                    player.dx = 669;
                } else {
                    player.sx += player.largura;
                    player.dx += player.velx;
                }
            } else if (c_espada>0) {
                player_sword = IMG_Load("harryd.png");
                SDL_FreeSurface(aux);
                if (player.dx>=669) {
                    player.sxesp += player.larguraesp;
                    player.dx = 669;
                } else {
                    player.sxesp += player.larguraesp;
                    player.dx += player.velx;
                }
            }
                subindo=0;
        } else if (player.dx>=0 && player.dy>414 && player.dy<419) {
            SDL_Surface *aux = playerImage;
            if (c_espada==0) {
                playerImage = IMG_Load("player.png");
                SDL_FreeSurface(aux);
                player.sx += player.largura;
                player.dx += player.velx;
            } else if (c_espada>0) {
                player_sword = IMG_Load("harryd.png");
                SDL_FreeSurface(aux);
                player.sxesp += player.larguraesp;
                player.dx += player.velx;
            }
                subindo=0;
        } else if (player.dx>=0 && player.dy>309 && player.dy<314) {
            SDL_Surface *aux = playerImage;
            if (c_espada==0) {
                playerImage = IMG_Load("player.png");
                SDL_FreeSurface(aux);
                if (player.dx>=669) {
                    player.sx += player.largura;
                    player.dx = 669;
                } else {
                    player.sx += player.largura;
                    player.dx += player.velx;
                }
            } else if (c_espada>0) {
                player_sword = IMG_Load("harryd.png");
                SDL_FreeSurface(aux);
                if (player.dx>=669) {
                    player.sxesp += player.larguraesp;
                    player.dx = 669;
                } else {
                    player.sxesp += player.larguraesp;
                    player.dx += player.velx;
                }
            }
            subindo=0;
        } else if (player.dx>=0 && player.dy>204 && player.dy<209) {
            SDL_Surface *aux = playerImage;
            if (c_espada==0) {
                playerImage = IMG_Load("player.png");
                SDL_FreeSurface(aux);
                if (player.dx>=669) {
                    player.sx += player.largura;
                    player.dx = 669;
                } else {
                    player.sx += player.largura;
                    player.dx += player.velx;
                }
            } else if (c_espada>0) {
               player_sword = IMG_Load("harryd.png");
                SDL_FreeSurface(aux);
                if (player.dx>=669) {
                    player.sxesp += player.larguraesp;
                    player.dx = 669;
                } else {
                    player.sxesp += player.larguraesp;
                    player.dx += player.velx;
                }
            }
                subindo=0;
        } else if (player.dx>=0 && player.dy>216 && player.dy<222) {
            SDL_Surface *aux = playerImage;
            if (c_espada==0) {
                playerImage = IMG_Load("player.png");
                SDL_FreeSurface(aux);
                player.sx += player.largura;
                player.dx += player.velx;
            } else if (c_espada>0) {
                player_sword = IMG_Load("harryd.png");
                SDL_FreeSurface(aux);
                player.sxesp += player.larguraesp;
                player.dx += player.velx;
            }
            subindo=0;
        } else if (player.dx>=0 && player.dy>116 && player.dy<124) {
            SDL_Surface *aux = playerImage;
            if (c_espada==0) {
                playerImage = IMG_Load("player.png");
                SDL_FreeSurface(aux);
                player.sx += player.largura;
                player.dx += player.velx;
            } else if (c_espada>0) {
                player_sword = IMG_Load("harryd.png");
                SDL_FreeSurface(aux);
                player.sxesp += player.larguraesp;
                player.dx += player.velx;
            }
            subindo=0;
        }else if (pulo==1) {
            if (personagem.y+personagem.h<560 && check_collision(personagem, p_1)==0 && check_collision(personagem, p_2)==0
             && check_collision(personagem, p_3)==0 && check_collision(personagem, p_4)==0 && check_collision(personagem, p_5)==0 && jump>0) {

                if (player.dx<=669 && player.dx<=tam_pulo) {
                    SDL_Surface *aux = playerImage;
                    playerImage = IMG_Load("pular_1.png");
                    SDL_FreeSurface(aux);
                    player.dx += player.velx;
                    subindo=0;
                }
            }

        }
    }

     if(teclaEsquerda)
    {
        bdireita=0;
        besquerda=1;
        if ((player.dx>0 && player.dy>518 && player.dy<522)) {
            SDL_Surface *aux = playerImage;
            if (c_espada==0) {
                playerImage = IMG_Load("player_1.png");
                SDL_FreeSurface(aux);
                player.sx -= player.largura;
                player.dx -= player.velx;
            } else if (c_espada>0) {
                player_sword = IMG_Load("harrye.png");
                SDL_FreeSurface(aux);
                player.sxesp -= player.larguraesp;
                player.dx -= player.velx;
            }
            subindo=0;
        } else if (player.dy>414 && player.dy<419 && player.dx>69) {
            SDL_Surface *aux = playerImage;
            if (c_espada==0) {
                playerImage = IMG_Load("player_1.png");
                SDL_FreeSurface(aux);
                if (player.dx<=70) {
                    player.sx -= player.largura;
                    player.dx = 70;
                } else {
                    player.sx -= player.largura;
                    player.dx -= player.velx;
                }
            } else if (c_espada>0) {
                player_sword = IMG_Load("harrye.png");
                SDL_FreeSurface(aux);
                if (player.dx<=70) {
                    player.sxesp -= player.larguraesp;
                    player.dx = 70;
                } else {
                    player.sxesp -= player.larguraesp;
                    player.dx -= player.velx;
                }
            }
            subindo=0;
        } else if (player.dx>=0 && player.dy>309 && player.dy<314) {
            SDL_Surface *aux = playerImage;
            if (c_espada==0) {
                playerImage = IMG_Load("player_1.png");
                SDL_FreeSurface(aux);
                player.sx -= player.largura;
                player.dx -= player.velx;
            } else if (c_espada>0) {
                player_sword = IMG_Load("harrye.png");
                SDL_FreeSurface(aux);
                player.sxesp -= player.larguraesp;
                player.dx -= player.velx;
            }
            subindo=0;
        } else if (player.dx>69 && player.dy>216 && player.dy<222) {
            SDL_Surface *aux = playerImage;
            if (c_espada==0) {
                playerImage = IMG_Load("player_1.png");
                SDL_FreeSurface(aux);
                if (player.dx<=70) {
                    player.sx -= player.largura;
                    player.dx = 70;
                } else {
                    player.sx -= player.largura;
                    player.dx -= player.velx;
                }
            } else if (c_espada>0) {
                player_sword = IMG_Load("harrye.png");
                SDL_FreeSurface(aux);
                if (player.dx<=70) {
                    player.sxesp -= player.larguraesp;
                    player.dx = 70;
                } else {
                    player.sxesp -= player.larguraesp;
                    player.dx -= player.velx;
                }
            }
            subindo=0;
        } else if (player.dx>600 && player.dy>116 && player.dy<124) {
            SDL_Surface *aux = playerImage;
            if (c_espada==0) {
                playerImage = IMG_Load("player_1.png");
                SDL_FreeSurface(aux);
                if (player.dx<=601) {
                    player.sx -= player.largura;
                    player.dx = 601;
                } else {
                    player.sx -= player.largura;
                    player.dx -= player.velx;
                }
            } else if (c_espada>0) {
                player_sword = IMG_Load("harrye.png");
                SDL_FreeSurface(aux);
                if (player.dx<=601) {
                    player.sxesp -= player.larguraesp;
                    player.dx = 601;
                } else {
                    player.sxesp -= player.larguraesp;
                    player.dx -= player.velx;
                }
            }
            subindo=0;
        } else if (pulo==1) {
            if (personagem.y+personagem.h<560 && check_collision(personagem, p_1)==0 && check_collision(personagem, p_2)==0
             && check_collision(personagem, p_3)==0 && check_collision(personagem, p_4)==0 && check_collision(personagem, p_5)==0 && jump>0) {
            if (pulo==0 || pulo==1)
                if (player.dx>=70 && player.dx<=tam_pulo) {
                    SDL_Surface *aux = playerImage;
                    playerImage = IMG_Load("pular_1.png");
                    SDL_FreeSurface(aux);
                    player.dx -= player.velx;
                    subindo=0;
                }
            }
        }
    }
     if(teclaCima==1 && c_espada==0)
    {   if ((player.dx>185 && player.dx<212 && player.dy>417) || (player.dx>335 && player.dx<362 && player.dy>312 && player.dy<416)
            || (player.dx>69 && player.dx<96 && player.dy>220 && player.dy<320)
            || (player.dx>714 && player.dx<750 && player.dy>120 && player.dy<218)) {
            SDL_Surface *aux = player_subir;
            player_subir = IMG_Load("subir_1.png");
            player.up+=55;
            SDL_FreeSurface(aux);
            player.dy -= player.vely;
            subindo=1;
        }
    }
     if(teclaBaixo==1 && c_espada==0)
    {
        if (player.dx>185 && player.dx<212 && player.dy>415 && player.dy<521) {
            SDL_Surface *aux = player_subir;
            player_subir = IMG_Load("subir_1.png");
            SDL_FreeSurface(aux);
            player.up-=55;
            if (player.dy<520)
                player.dy += player.vely;
            subindo=1;
        } else if (player.dx>335 && player.dx<362 && player.dy>310 && player.dy<416) {
            SDL_Surface *aux = player_subir;
            player_subir = IMG_Load("subir_1.png");
            SDL_FreeSurface(aux);
            player.up-=55;
            if (player.dy<415)
                player.dy += player.vely;
            subindo=1;
        } else if (player.dx>69 && player.dx<96 && player.dy>217 && player.dy<312) {
            SDL_Surface *aux = player_subir;
            player_subir = IMG_Load("subir_1.png");
            SDL_FreeSurface(aux);
            player.up-=55;
            if (player.dy<306)
                player.dy += player.vely;
            subindo=1;
        } else if (player.dx>714 && player.dx<750) {
            SDL_Surface *aux = player_subir;
            player_subir = IMG_Load("subir_1.png");
            SDL_FreeSurface(aux);
            player.up-=55;
            if (player.dy<214)
                player.dy += player.vely;
            subindo=1;
        }
    }
     if(teclaEspaco && c_espada==0)
    {
            SDL_Surface *aux = playerImage;
            if (teclaDireita==1) {
                playerImage = IMG_Load("pular_1.png");
                /*if (p_cima==1 || p_baixo==1) {
                    //SDL_Surface *aux = playerImage;
                    //playerImage = IMG_Load("pular_1.png");
                    SDL_FreeSurface(aux);
                    player.dx += player.velx;
                    subindo=0;
                }*/
            } else if (teclaEsquerda==1) {
                playerImage = IMG_Load("pular_2.png");
            } else {
                playerImage = IMG_Load("pular_1.png");
            }
            SDL_FreeSurface(aux);
            if (pulo==1) {
                jump++;
            }
            if (jump>0) {
                p_cima=1;
                p_baixo=0;
            }
            if (jump>10) {
                p_baixo=1;
                p_cima=0;
            }
            if (jump>20) {
                jump=0;
                pulo=0;
                p_baixo=0;
                p_cima=0;
            }
            if(p_cima) {
                player.dy-=4;
            } else if (p_baixo) {
                player.dy+=4;
            }
    }
}

void liberar() {
    SDL_FreeSurface(background);
    SDL_FreeSurface(playerImage);
    SDL_FreeSurface(plataforma);
    SDL_FreeSurface(escada);
    SDL_FreeSurface(voldemort_s);
    SDL_FreeSurface(gold);
    SDL_FreeSurface(player_subir);
    SDL_FreeSurface(player_sword);
    SDL_FreeSurface(plataforma_pequena);
    SDL_FreeSurface(fireball);
    SDL_FreeSurface(menu);
    SDL_FreeSurface(game_over);
    SDL_FreeSurface(pontos);
    SDL_FreeSurface(perdeu_vida);
    SDL_FreeSurface(vidas);
    SDL_FreeSurface(vidas_);
    SDL_FreeSurface(pontos);
    SDL_FreeSurface(score_);
    SDL_FreeSurface(tempo_restante);
    SDL_FreeSurface(minutos);
    SDL_FreeSurface(segundos);
    SDL_FreeSurface(Espada);
    SDL_FreeSurface(tempo_espada);
    Mix_FreeMusic(musica);
    Mix_FreeMusic(principal);
    TTF_CloseFont(t_1);
    TTF_Quit();
}

void eventoTeclado()
{
	   if(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT) exit(0);

        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_RIGHT: teclaDireita = 1;
                     break;
                case SDLK_LEFT: teclaEsquerda = 1;
                     break;
                case SDLK_ESCAPE: jogoRodando = 0;
                     liberar();
                     SDL_Quit();
                     break;
                case SDLK_UP: teclaCima = 1;
                     break;
                case SDLK_DOWN: teclaBaixo = 1;
                     break;
                case SDLK_SPACE: teclaEspaco = 1;
                     if (jump<=20 && c_espada==0) {
                        pulo=1;
                        if (tam_pulo==0)
                            tam_pulo=40+player.dx;
                     }
                     break;
            }
        }

         if(event.type == SDL_KEYUP)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_RIGHT: teclaDireita = 0;
                     break;
                case SDLK_LEFT: teclaEsquerda = 0;
                     break;
                case SDLK_UP: teclaCima = 0;
                     break;
                case SDLK_DOWN: teclaBaixo = 0;
                     break;
                case SDLK_SPACE: teclaEspaco = 0;
                    pulo=0;
                    tam_pulo=0;
                    break;
            }
        }

    }

    andar();
}


void pomo_voldemort_fireball() {
   v[0].x=0;
   v[0].y=0;
   v[0].w=50;
   v[0].h=28;
   v[1].x=50;
   v[1].y=0;
   v[1].w=50;
   v[1].h=28;
   v[2].x=100;
   v[2].y=0;
   v[2].w=50;
   v[2].h=28;
   v[3].x=150;
   v[3].y=0;
   v[3].w=50;
   v[3].h=28;

   voldemort[0].x=0;
   voldemort[0].y=0;
   voldemort[0].w=50;
   voldemort[0].h=80;
   voldemort[1].x=50;
   voldemort[1].y=0;
   voldemort[1].w=50;
   voldemort[1].h=80;
   voldemort[2].x=100;
   voldemort[2].y=0;
   voldemort[2].w=50;
   voldemort[2].h=80;

   Gina[0].x=0;
   Gina[0].y=0;
   Gina[0].w=60;
   Gina[0].h=60;
   Gina[1].x=60;
   Gina[1].y=0;
   Gina[1].w=60;
   Gina[1].h=60;
   Gina[2].x=120;
   Gina[2].y=0;
   Gina[2].w=60;
   Gina[2].h=60;

   sword[0].x=0;
   sword[0].y=0;
   sword[0].w=21;
   sword[0].h=80;
   sword[1].x=21;
   sword[1].y=0;
   sword[1].w=21;
   sword[1].h=80;

   snake.x = 620;
   snake.y = 110;
   snake.w = Gina->w;
   snake.h = Gina->h;

   esp_sword.x=550;
   esp_sword.y=285;
   esp_sword.w=21;
   esp_sword.h=80;

   if (lifes==4) {
        f.x = 80;
        f.y = 65;
        f.w = 30;
        f.h = 30;
        f1.x = 80;
        f1.y = 65;
        f1.w = 30;
        f1.h = 30;
        f2.x = 80;
        f2.y = 65;
        f2.w = 30;
        f2.h = 30;
        f3.x = 80;
        f3.y = 65;
        f3.w = 30;
        f3.h = 30;
        f4.x = 80;
        f4.y = 65;
        f4.w = 30;
        f4.h = 30;
    }

   g.x=510;
   g.y=510;
   g.w=50;
   g.h=28;

   g_1.x=565;
   g_1.y=420;
   g_1.w=50;
   g_1.h=28;

   g_2.x=10;
   g_2.y=315;
   g_2.w=50;
   g_2.h=28;

   g_3.x=495;
   g_3.y=210;
   g_3.w=50;
   g_3.h=28;

   butao.x = 303;
   butao.y = 184;
   butao.w = 175;
   butao.h = 71;

   sim.x = 229;
   sim.y = 444;
   sim.w = 113;
   sim.h = 58;

   nao.x = 460;
   nao.y = 444;
   nao.w = 110;
   nao.h = 58;

   voltar.x = 475;
   voltar.y = 412;
   voltar.w = 102;
   voltar.h = 53;

   rec_1.x = 297;
   rec_1.y = 367;
   rec_1.w = 186;
   rec_1.h = 53;

   creditos.x = 42;
   creditos.y = 367;
   creditos.w = 186;
   creditos.h = 53;

   controles.x = 537;
   controles.y = 367;
   controles.w = 186;
   controles.h = 53;

   tentar.x = 225;
   tentar.y = 423;
   tentar.w = 105;
   tentar.h = 55;

}

void construir_plataformas() {
   p.w = plataforma->w;
   p.h = 30;
   p_1.w = plataforma->w;
   p_1.h = plataforma->h;
   p_2.w = plataforma->w;
   p_2.h = plataforma->h;
   p_3.w = plataforma_menor->w;
   p_3.h = plataforma_menor->h;
   p_4.w = plataforma_pequena->w;
   p_4.h = plataforma_pequena->h;
   p_5.w = plataforma->w;
   p_5.h = plataforma->h;
   p.x = 0;
   p.y = 570;
   SDL_BlitSurface(plataforma, 0, screen, &p);
   p_1.x = 79;
   p_1.y = 470;
   SDL_BlitSurface(plataforma, 0, screen, &p_1);
   p_2.x = 0;
   p_2.y = 369;
   SDL_BlitSurface(plataforma, 0, screen, &p_2);
   p_5.x = 79;
   p_5.y = 270;
   SDL_BlitSurface(plataforma, 0, screen, &p_5);
   p_4.x = 0;
   p_4.y = 128;
   SDL_BlitSurface(plataforma_pequena, 0, screen, &p_4);
   p_3.x = 600;
   p_3.y = 168;
   SDL_BlitSurface(plataforma_menor, 0, screen, &p_3);
}

void firebola (int time) {
        if (time>=100 && time<200) {
            fr=1;
        } else if (time>=200 && time<400) {
            fr=2;
        } else if (time>=400 && time<600) {
            fr=3;
        } else if (time>=600 && time<800) {
            fr=4;
        } else if (time>=800) {
            fr=5;
        }

        if (fr>=1) {
            if (f.y==65 && f.x<=495) {
                direita=1;
                baixo=0;
                esquerda=0;
            } else if (f.x==500 && f.y<241) {
                direita=0;
                baixo=1;
                esquerda=0;
            } else if (f.y==241 && f.x>=90){
                direita=0;
                baixo=0;
                esquerda=1;
            } else if (f.x==85 && f.y<341){
                direita=0;
                baixo=1;
                esquerda=0;
            } else if (f.y==341 && f.x<=355){
                direita=1;
                esquerda=0;
                baixo=0;
            } else if (f.x==360 && f.y<441){
                direita=0;
                esquerda=0;
                baixo=1;
            } else if (f.y==441 && f.x>=210){
                direita=0;
                esquerda=1;
                baixo=0;
            } else if (f.x==205 && f.y<541){
                direita=0;
                esquerda=0;
                baixo=1;
            } else if (f.y==541 && f.x<=720){
                direita=1;
                esquerda=0;
                baixo=0;
            } else if (f.x==725 && f.y<630){
                direita=0;
                esquerda=0;
                baixo=1;
            } else {
                f.x=80;
                f.y=65;
                bateu=0;
                direita=0;
                esquerda=0;
                baixo=0;
                marcar=0;
            }
        }
        if (fr>=2) {
            if (f1.y==65 && f1.x<=495) {
                direita1=1;
                baixo1=0;
                esquerda1=0;
            } else if (f1.x==500 && f1.y<241) {
                direita1=0;
                baixo1=1;
                esquerda1=0;
            } else if (f1.y==241 && f1.x>=90){
                direita1=0;
                baixo1=0;
                esquerda1=1;
            } else if (f1.x==85 && f1.y<341){
                direita1=0;
                baixo1=1;
                esquerda1=0;
            } else if (f1.y==341 && f1.x<=355){
                direita1=1;
                esquerda1=0;
                baixo1=0;
            } else if (f1.x==360 && f1.y<441){
                direita1=0;
                esquerda1=0;
                baixo1=1;
            } else if (f1.y==441 && f1.x>=210){
                direita1=0;
                esquerda1=1;
                baixo1=0;
            } else if (f1.x==205 && f1.y<541){
                direita1=0;
                esquerda1=0;
                baixo1=1;
            } else if (f1.y==541 && f1.x<=720){
                direita1=1;
                esquerda1=0;
                baixo1=0;
            } else if (f1.x==725 && f1.y<630){
                direita1=0;
                esquerda1=0;
                baixo1=1;
            } else {
                f1.x=120;
                f1.y=65;
                bateu1=0;
                direita1=0;
                esquerda1=0;
                baixo1=0;
                marcar1=0;
            }
        }
           if (fr>=3) {
            if (f2.y==65 && f2.x<=495) {
                direita2=1;
                baixo2=0;
                esquerda2=0;
            } else if (f2.x==500 && f2.y<241) {
                direita2=0;
                baixo2=1;
                esquerda2=0;
            } else if (f2.y==241 && f2.x>=90){
                direita2=0;
                baixo2=0;
                esquerda2=1;
            } else if (f2.x==85 && f2.y<341){
                direita2=0;
                baixo2=1;
                esquerda2=0;
            } else if (f2.y==341 && f2.x<=355){
                direita2=1;
                esquerda2=0;
                baixo2=0;
            } else if (f2.x==360 && f2.y<441){
                direita2=0;
                esquerda2=0;
                baixo2=1;
            } else if (f2.y==441 && f2.x>=210){
                direita2=0;
                esquerda2=1;
                baixo2=0;
            } else if (f2.x==205 && f2.y<541){
                direita2=0;
                esquerda2=0;
                baixo2=1;
            } else if (f2.y==541 && f2.x<=720){
                direita2=1;
                esquerda2=0;
                baixo2=0;
            } else if (f2.x==725 && f2.y<630){
                direita2=0;
                esquerda2=0;
                baixo2=1;
            } else {
                f2.x=120;
                f2.y=65;
                bateu2=0;
                direita2=0;
                esquerda2=0;
                baixo2=0;
                marcar2=0;
            }
        }
        if (fr>=4) {
            if (f3.y==65 && f3.x<=495) {
                direita3=1;
                baixo3=0;
                esquerda3=0;
            } else if (f3.x==500 && f3.y<241) {
                direita3=0;
                baixo3=1;
                esquerda3=0;
            } else if (f3.y==241 && f3.x>=90){
                direita3=0;
                baixo3=0;
                esquerda3=1;
            } else if (f3.x==85 && f3.y<341){
                direita3=0;
                baixo3=1;
                esquerda3=0;
            } else if (f3.y==341 && f3.x<=355){
                direita3=1;
                esquerda3=0;
                baixo3=0;
            } else if (f3.x==360 && f3.y<441){
                direita3=0;
                esquerda3=0;
                baixo3=1;
            } else if (f3.y==441 && f3.x>=210){
                direita3=0;
                esquerda3=1;
                baixo3=0;
            } else if (f3.x==205 && f3.y<541){
                direita3=0;
                esquerda3=0;
                baixo3=1;
            } else if (f3.y==541 && f3.x<=720){
                direita3=1;
                esquerda3=0;
                baixo3=0;
            } else if (f3.x==725 && f3.y<630){
                direita3=0;
                esquerda3=0;
                baixo3=1;
            } else {
                f3.x=120;
                f3.y=65;
                bateu3=0;
                direita3=0;
                esquerda3=0;
                baixo3=0;
                marcar3=0;
            }
        }
        if (fr>=5) {
            if (f4.y==65 && f4.x<=495) {
                direita4=1;
                baixo4=0;
                esquerda4=0;
            } else if (f4.x==500 && f4.y<241) {
                direita4=0;
                baixo4=1;
                esquerda4=0;
            } else if (f4.y==241 && f4.x>=90){
                direita4=0;
                baixo4=0;
                esquerda4=1;
            } else if (f4.x==85 && f4.y<341){
                direita4=0;
                baixo4=1;
                esquerda4=0;
            } else if (f4.y==341 && f4.x<=355){
                direita4=1;
                esquerda4=0;
                baixo4=0;
            } else if (f4.x==360 && f4.y<441){
                direita4=0;
                esquerda4=0;
                baixo4=1;
            } else if (f4.y==441 && f4.x>=210){
                direita4=0;
                esquerda4=1;
                baixo4=0;
            } else if (f4.x==205 && f4.y<541){
                direita4=0;
                esquerda4=0;
                baixo4=1;
            } else if (f4.y==541 && f4.x<=720){
                direita4=1;
                esquerda4=0;
                baixo4=0;
            } else if (f4.x==725 && f4.y<630){
                direita4=0;
                esquerda4=0;
                baixo4=1;
            } else {
                f4.x=120;
                f4.y=65;
                bateu4=0;
                direita4=0;
                esquerda4=0;
                baixo4=0;
                marcar4=0;
            }
        }
}

void mov_fireball() {
        if (direita==1) {
            fogo.sx+=30;
            f.x+=5;
        }
        if (baixo==1){
            fogo.sx+=30;
            f.y+=4;
        }
        if (esquerda==1) {
            fogo.sx+=30;
            f.x-=5;
        }

        if (direita1==1) {
            fogo_1.sx+=30;
            f1.x+=5;
        }
        if (baixo1==1){
            fogo_1.sx+=30;
            f1.y+=4;
        }
        if (esquerda1==1) {
            fogo_1.sx+=30;
            f1.x-=5;
        }
        if (direita2==1) {
            fogo_2.sx+=30;
            f2.x+=5;
        }
        if (baixo2==1){
            fogo_2.sx+=30;
            f2.y+=4;
        }
        if (esquerda2==1) {
            fogo_2.sx+=30;
            f2.x-=5;
        }
        if (direita3==1) {
            fogo_3.sx+=30;
            f3.x+=5;
        }
        if (baixo3==1){
            fogo_3.sx+=30;
            f3.y+=4;
        }
        if (esquerda3==1) {
            fogo_3.sx+=30;
            f3.x-=5;
        }
        if (direita4==1) {
            fogo_4.sx+=30;
            f4.x+=5;
        }
        if (baixo4==1){
            fogo_4.sx+=30;
            f4.y+=4;
        }
        if (esquerda4==1) {
            fogo_4.sx+=30;
            f4.x-=5;
        }
}

void condicao_fogo (){
        if (fogo.sx>=210) {
            fogo.sx=0;
        }
        if (fogo.sx<0) {
            fogo.sx=210;
        }
        if (fogo_1.sx>=210) {
            fogo_1.sx=0;
        }
        if (fogo_1.sx<0) {
            fogo_1.sx=210;
        }
        if (fogo_2.sx>=210) {
            fogo_2.sx=0;
        }
        if (fogo_2.sx<0) {
            fogo_2.sx=210;
        }
        if (fogo_3.sx>=210) {
            fogo_3.sx=0;
        }
        if (fogo_3.sx<0) {
            fogo_3.sx=210;
        }
        if (fogo_4.sx>=210) {
            fogo_4.sx=0;
        }
        if (fogo_4.sx<0) {
            fogo_4.sx=210;
        }
}

int arquivo() {
    int i=1, recorde, j=0, g;
    int a, b, d;
    char c_1[3][10], f_1[3][10];
    FILE *arq;
    arq=fopen("arquivo.txt", "r");
    if (arq!=NULL) {
        FILE *arq;
        arq=fopen("arquivo.txt", "r");
        while(j<=2) {
            fscanf(arq,"%s %s", c_1[j], f_1[j]);
            j++;
        }
        a=atoi(c_1[0]);
        b=atoi(c_1[1]);
        d=atoi(c_1[2]);
        fclose(arq);
        if (pontuacao_final>a || pontuacao_final>b || pontuacao_final>d) {
            return 1;
        } else {
            return 0;
        }
    }
}

void arquivo_gravar(const char *s_y, int s_z) {
    int i=1,j=0, g;
    int a, b, d;
    char c_1[3][10], f_1[3][10], c[20];
    char *y;
    y=(char*) s_y;
    FILE *arq;
    arq=fopen("arquivo.txt", "r");
    if (arq!=NULL) {
        while(j<=2) {
            fscanf(arq,"%s %s", c_1[j], f_1[j]);
            j++;
        }
        a=atoi(c_1[0]);
        b=atoi(c_1[1]);
        d=atoi(c_1[2]);
        fclose(arq);
        arq=fopen("arquivo_1.txt", "w+");
        if (s_z>a) {
            fprintf(arq, "%d %s\n", s_z, y);
            fprintf(arq, "%d %s\n", a, f_1[0]);
            fprintf(arq, "%d %s\n", b, f_1[1]);
        } else if (s_z>b) {
            fprintf(arq, "%d %s\n", a, f_1[0]);
            fprintf(arq, "%d %s\n", s_z, y);
            fprintf(arq, "%d %s\n", b, f_1[1]);
        } else if (s_z>d) {
            fprintf(arq, "%d %s\n", a, f_1[0]);
            fprintf(arq, "%d %s\n", b, f_1[1]);
            fprintf(arq, "%d %s\n", s_z, y);
        }
        fclose(arq);
        arq=fopen("arquivo_1.txt", "r");
        FILE *arq_2;
        arq_2=fopen("arquivo.txt", "w+");
        j=0;
        while(j<=2) {
            fscanf(arq,"%s %s", c_1[j], f_1[j]);
            fprintf(arq_2, "%s %s\n", c_1[j], f_1[j]);
            j++;
        }
        fclose(arq);
        fclose(arq_2);
    }
}

int mostrarmenu (SDL_Surface *tela) {
    Uint32 tempo;
    int x, y;
    SDL_Event event;
    while (1) {
        tempo=SDL_GetTicks();
        SDL_BlitSurface(tela, 0, screen, 0);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    liberar();
                    return 0;
                    SDL_Quit();
                    break;
                case SDLK_ESCAPE:
                    liberar();
                    return 0;
                    SDL_Quit();
                    break;
                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button==SDL_BUTTON_LEFT) {
                        x = event.button.x;
                        y = event.button.y;
                        if (( x > butao.x ) && ( x < butao.x + butao.w ) && ( y > butao.y ) && ( y < butao.y + butao.h )) {
                            return 1;
                        }
                        if (( x > rec_1.x ) && ( x < rec_1.x + rec_1.w ) && ( y > rec_1.y ) && ( y < rec_1.y + rec_1.h )) {
                            return 2;
                        }
                        if (( x > creditos.x ) && ( x < creditos.x + creditos.w ) && ( y > creditos.y ) && ( y < creditos.y + creditos.h )) {
                            return 3;
                        }
                        if (( x > controles.x ) && ( x < controles.x + controles.w ) && ( y > controles.y ) && ( y < controles.y + controles.h )) {
                            return 4;
                        }
                    }
                    break;
            }
            SDL_Flip(screen);
                if(1000/30 > (SDL_GetTicks()-tempo))
                        SDL_Delay(1000/30 - (SDL_GetTicks()-tempo));
        }
    }
}

int mostrarsimples (int imagem) {
    Uint32 tempo;
    int x, y, i=1,j=0, g=0;
    char c_1[3][10], f_1[3][10];
    SDL_Event event;
    SDL_Surface *text;
    while (1) {
        tempo=SDL_GetTicks();
        if (imagem==1) {
            SDL_BlitSurface(Recorde, 0, screen, 0);
        } else if (imagem==2) {
            SDL_BlitSurface(Creditos, 0, screen, 0);
        } else if (imagem==3) {
            SDL_BlitSurface(Controles, 0, screen, 0);
        }
        if (imagem==1) {
            FILE *arq;
            arq=fopen("arquivo.txt", "r");
            //fscanf(arq,"%d %s", c_1[j], f_1[j]);
            while(j<=2) {
                fscanf(arq,"%s %s", c_1[j], f_1[j]);
                j++;
            }
            fclose(arq);
            fontes.x = 310;
            fontes.y = 212;
            text = TTF_RenderText_Solid(t_1, (char *) c_1[0], {0, 0, 0} );
            SDL_BlitSurface (text, 0, screen, &fontes);
            fontes.y = 312;
            text = TTF_RenderText_Solid(t_1, (char *) c_1[1], {0, 0, 0} );
            SDL_BlitSurface (text, 0, screen, &fontes);
            fontes.y = 412;
            text = TTF_RenderText_Solid(t_1, (char *) c_1[2], {0, 0, 0} );
            SDL_BlitSurface (text, 0, screen, &fontes);
            fontes.x = 210;
            fontes.y = 216;
            text = TTF_RenderText_Solid(t_1, (char *) f_1[0], {0, 0, 0} );
            SDL_BlitSurface (text, 0, screen, &fontes);
            fontes.y = 316;
            text = TTF_RenderText_Solid(t_1, (char *) f_1[1], {0, 0, 0} );
            SDL_BlitSurface (text, 0, screen, &fontes);
            fontes.y = 416;
            text = TTF_RenderText_Solid(t_1, (char *) f_1[2], {0, 0, 0} );
            SDL_BlitSurface (text, 0, screen, &fontes);
        }
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    liberar();
                    return 0;
                    SDL_Quit();
                    break;
                case SDLK_ESCAPE:
                    liberar();
                    return 0;
                    SDL_Quit();
                    break;
                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button==SDL_BUTTON_LEFT) {
                        x = event.button.x;
                        y = event.button.y;
                        if (( x > 186 ) && ( x < 186 + 75 ) && ( y > 511 ) && ( y < 511 + 42 )) {
                            return 2;
                        }
                    }
                    break;
            }
            SDL_Flip(screen);
                if(1000/30 > (SDL_GetTicks()-tempo))
                        SDL_Delay(1000/30 - (SDL_GetTicks()-tempo));
            }
        }
}

int mostrarperder (SDL_Surface *tela) {
    Uint32 tempo;
    int x, y;
    SDL_Event event;
    while (1) {
        tempo=SDL_GetTicks();
        SDL_BlitSurface(tela, 0, screen, 0);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    liberar();
                    return 0;
                    SDL_Quit();
                    break;
                case SDLK_ESCAPE:
                    liberar();
                    return 0;
                    SDL_Quit();
                    break;
                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button==SDL_BUTTON_LEFT) {
                        x = event.button.x;
                        y = event.button.y;
                        if (( x > tentar.x ) && ( x < tentar.x + tentar.w ) && ( y > tentar.y ) && ( y < tentar.y + tentar.h )) {
                            return 1;
                        } else if (( x > voltar.x ) && ( x < voltar.x + voltar.w ) && ( y > voltar.y ) && ( y < voltar.y + voltar.h )) {
                            return 2;
                        }
                    }
            }
            SDL_Flip(screen);
                if(1000/30 > (SDL_GetTicks()-tempo))
                        SDL_Delay(1000/30 - (SDL_GetTicks()-tempo));
        }
        SDL_Flip(screen);
    }
}

int mostrarganho (SDL_Surface *tela) {
    Uint32 tempo;
    int x, y, i, rec=0;
    SDL_Event event;
    SDL_Surface *text = NULL;
    char maior[10], nada[10];
    std::string str;
    i=arquivo();
    while (1) {
        tempo=SDL_GetTicks();
        SDL_BlitSurface(tela, 0, screen, 0);
        std::stringstream c;
        c << " " << pontuacao_final;
        //pontuacao_final=pontuacao_final + t_restou/1000;
        fontes.x=108;
        fontes.y=274;
        SDL_Surface *score_1=TTF_RenderText_Solid(t_1, "Score: ", {0,0,0});
        SDL_BlitSurface(score_1, 0, screen, &fontes);
        score_1= TTF_RenderText_Solid( t_1, c.str().c_str(), {0, 0, 0});
        fontes.x=160;
        SDL_BlitSurface(score_1, 0, screen, &fontes);
        score_1 = TTF_RenderText_Solid(t_1, "Best Score: ", {0, 0, 0});
        fontes.x = 250;
        SDL_BlitSurface(score_1, 0, screen, &fontes);
        FILE *arq=fopen("arquivo.txt", "r");
        fscanf(arq,"%s %s", maior, nada);
        sprintf(maior, "%d", rec);
        if (rec>pontuacao_final) {
            score_1 = TTF_RenderText_Solid(t_1, maior, {0, 0, 0});
        } else {
            score_1 = TTF_RenderText_Solid(t_1, c.str().c_str(), {0, 0, 0});
        }
        fontes.x=370;
        SDL_BlitSurface(score_1, 0, screen, &fontes);
        fclose(arq);
        if (i==1) {
            score_1=TTF_RenderText_Solid(t_1, "Novo Recorde! Digite um nome: ", {0,0,0});
            fontes.x = 108;
            fontes.y = 320;
            SDL_BlitSurface(score_1, 0, screen, &fontes);
            SDL_EnableUNICODE(SDL_ENABLE);
        }
        while (SDL_PollEvent(&event)) {
            if (i==1) {
                if (event.type==SDL_KEYDOWN) {
                    std::string temp = str;
                    if( str.length()<3) {
                        if( event.key.keysym.unicode == (Uint16)' ' ) {
                            str += (char)event.key.keysym.unicode;
                        } else if((event.key.keysym.unicode>=(Uint16)'0')&&(event.key.keysym.unicode<=(Uint16)'9')) {
                            str += (char)event.key.keysym.unicode;
                        } else if((event.key.keysym.unicode>=(Uint16)'A')&&(event.key.keysym.unicode<=(Uint16)'Z')) {
                            str += (char)event.key.keysym.unicode;
                        } else if((event.key.keysym.unicode>=(Uint16)'a')&&(event.key.keysym.unicode<=(Uint16)'z')) {
                            str += (char)event.key.keysym.unicode;
                        }
                    }
                    if((event.key.keysym.sym==SDLK_BACKSPACE)&&(str.length()!=0)) {
                        str.erase( str.length() - 1 );
                    }
                    if(str!=temp) {
                        SDL_FreeSurface( text );
                        text =TTF_RenderText_Solid(t_1,str.c_str(), {0,0,0});
                    }
                }
            }
            switch (event.type) {
                case SDL_QUIT:
                    liberar();
                    return 0;
                    SDL_Quit();
                    break;
                case SDLK_ESCAPE:
                    liberar();
                    return 0;
                    SDL_Quit();
                    break;
                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button==SDL_BUTTON_LEFT) {
                        x = event.button.x;
                        y = event.button.y;
                        if (( x > sim.x ) && ( x < sim.x + sim.w ) && ( y > sim.y ) && ( y < sim.y + sim.h )) {
                            if (text!=NULL && i==1) {
                                arquivo_gravar(str.c_str(), pontuacao_final);
                                return 1;
                            }
                            if (i==0) {
                                return 1;
                            }
                        } else if (( x > nao.x ) && ( x < nao.x + nao.w ) && ( y > nao.y ) && ( y < nao.y + nao.h )) {
                            if (text!=NULL && i==1) {
                                arquivo_gravar(str.c_str(), pontuacao_final);
                                return 2;
                            }
                            if (i==0) {
                                return 2;
                            }
                        }
                    }
            }
            fontes.x=400;
            SDL_BlitSurface(text, 0, screen, &fontes);
            SDL_Flip(screen);
            if(1000/30 > (SDL_GetTicks()-tempo))
                        SDL_Delay(1000/30 - (SDL_GetTicks()-tempo));
        }
    }
}

void marcar_p_pulo () {
    if (bdireita==1) {
       if (personagem.y>=469 && personagem.y<=570 && f.y>=520 && f.y<=570) {
        if (check_collision(personagem, f)==0 && pulo!=0 && personagem.x+personagem.w>f.x+f.w && fds==0) {
            fds++;
            score+=100;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=469 && personagem.y<=570 && f1.y>=520 && f1.y<=570) {
        if (check_collision(personagem, f1)==0 && pulo!=0 && personagem.x+personagem.w>f1.x+f1.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=469 && personagem.y<=570 && f2.y>=520 && f2.y<=570) {
        if (check_collision(personagem, f2)==0 && pulo!=0 && personagem.x+personagem.w>f2.x+f2.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=469 && personagem.y<=570 && f3.y>=520 && f3.y<=570) {
        if (check_collision(personagem, f3)==0 && pulo!=0 && personagem.x+personagem.w>f3.x+f3.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=469 && personagem.y<=570 && f4.y>=520 && f4.y<=570) {
        if (check_collision(personagem, f4)==0 && pulo!=0 && personagem.x+personagem.w>f4.x+f4.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=369 && personagem.y<=470 && f.y>=420 && f.y<=470) {
        if (check_collision(personagem, f)==0 && pulo!=0 && personagem.x+personagem.w>f.x+f.w && fds==0) {
            fds++;
            score+=100;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=369 && personagem.y<=470 && f1.y>=420 && f1.y<=470) {
        if (check_collision(personagem, f1)==0 && pulo!=0 && personagem.x+personagem.w>f1.x+f1.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=369 && personagem.y<=470 && f2.y>=420 && f2.y<=470) {
        if (check_collision(personagem, f2)==0 && pulo!=0 && personagem.x+personagem.w>f2.x+f2.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=369 && personagem.y<=470 && f3.y>=420 && f3.y<=470) {
        if (check_collision(personagem, f3)==0 && pulo!=0 && personagem.x+personagem.w>f3.x+f3.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=369 && personagem.y<=470 && f4.y>=420 && f4.y<=470) {
        if (check_collision(personagem, f4)==0 && pulo!=0 && personagem.x+personagem.w>f4.x+f4.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=269 && personagem.y<=370 && f.y>=320 && f.y<=370) {
        if (check_collision(personagem, f)==0 && pulo!=0 && personagem.x+personagem.w>f.x+f.w && fds==0) {
            fds++;
            score+=100;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=269 && personagem.y<=370 && f1.y>=320 && f1.y<=370) {
        if (check_collision(personagem, f1)==0 && pulo!=0 && personagem.x+personagem.w>f1.x+f1.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=269 && personagem.y<=370 && f2.y>=320 && f2.y<=370) {
        if (check_collision(personagem, f2)==0 && pulo!=0 && personagem.x+personagem.w>f2.x+f2.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=269 && personagem.y<=370 && f3.y>=320 && f3.y<=370) {
        if (check_collision(personagem, f3)==0 && pulo!=0 && personagem.x+personagem.w>f3.x+f3.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=269 && personagem.y<=370 && f4.y>=320 && f4.y<=370) {
        if (check_collision(personagem, f4)==0 && pulo!=0 && personagem.x+personagem.w>f4.x+f4.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=169 && personagem.y<=270 && f.y>=220 && f.y<=270) {
        if (check_collision(personagem, f)==0 && pulo!=0 && personagem.x+personagem.w>f.x+f.w && fds==0) {
            fds++;
            score+=100;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=169 && personagem.y<=270 && f1.y>=220 && f1.y<=270) {
        if (check_collision(personagem, f1)==0 && pulo!=0 && personagem.x+personagem.w>f1.x+f1.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=169 && personagem.y<=270 && f2.y>=220 && f2.y<=270) {
        if (check_collision(personagem, f2)==0 && pulo!=0 && personagem.x+personagem.w>f2.x+f2.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=169 && personagem.y<=270 && f3.y>=220 && f3.y<=270) {
        if (check_collision(personagem, f3)==0 && pulo!=0 && personagem.x+personagem.w>f3.x+f3.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=169 && personagem.y<=270 && f4.y>=220 && f4.y<=270) {
        if (check_collision(personagem, f4)==0 && pulo!=0 && personagem.x+personagem.w>f4.x+f4.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
    } else if (besquerda==1) {
       if (personagem.y>=469 && personagem.y<=570 && f.y>=520 && f.y<=570) {
        if (check_collision(personagem, f)==0 && pulo!=0 && personagem.x+personagem.w<f.x+f.w && fds==0) {
            fds++;
            score+=100;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=469 && personagem.y<=570 && f1.y>=520 && f1.y<=570) {
        if (check_collision(personagem, f1)==0 && pulo!=0 && personagem.x+personagem.w<f1.x+f1.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=469 && personagem.y<=570 && f2.y>=520 && f2.y<=570) {
        if (check_collision(personagem, f2)==0 && pulo!=0 && personagem.x+personagem.w<f2.x+f2.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=469 && personagem.y<=570 && f3.y>=520 && f3.y<=570) {
        if (check_collision(personagem, f3)==0 && pulo!=0 && personagem.x+personagem.w<f3.x+f3.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=469 && personagem.y<=570 && f4.y>=520 && f4.y<=570) {
        if (check_collision(personagem, f4)==0 && pulo!=0 && personagem.x+personagem.w<f4.x+f4.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=369 && personagem.y<=470 && f.y>=420 && f.y<=470) {
        if (check_collision(personagem, f)==0 && pulo!=0 && personagem.x+personagem.w<f.x+f.w && fds==0) {
            fds++;
            score+=100;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=369 && personagem.y<=470 && f1.y>=420 && f1.y<=470) {
        if (check_collision(personagem, f1)==0 && pulo!=0 && personagem.x+personagem.w<f1.x+f1.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=369 && personagem.y<=470 && f2.y>=420 && f2.y<=470) {
        if (check_collision(personagem, f2)==0 && pulo!=0 && personagem.x+personagem.w<f2.x+f2.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=369 && personagem.y<=470 && f3.y>=420 && f3.y<=470) {
        if (check_collision(personagem, f3)==0 && pulo!=0 && personagem.x+personagem.w<f3.x+f3.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=369 && personagem.y<=470 && f4.y>=420 && f4.y<=470) {
        if (check_collision(personagem, f4)==0 && pulo!=0 && personagem.x+personagem.w<f4.x+f4.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=269 && personagem.y<=370 && f.y>=320 && f.y<=370) {
        if (check_collision(personagem, f)==0 && pulo!=0 && personagem.x+personagem.w<f.x+f.w && fds==0) {
            fds++;
            score+=100;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=269 && personagem.y<=370 && f1.y>=320 && f1.y<=370) {
        if (check_collision(personagem, f1)==0 && pulo!=0 && personagem.x+personagem.w<f1.x+f1.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=269 && personagem.y<=370 && f2.y>=320 && f2.y<=370) {
        if (check_collision(personagem, f2)==0 && pulo!=0 && personagem.x+personagem.w<f2.x+f2.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=269 && personagem.y<=370 && f3.y>=320 && f3.y<=370) {
        if (check_collision(personagem, f3)==0 && pulo!=0 && personagem.x+personagem.w<f3.x+f3.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=269 && personagem.y<=370 && f4.y>=320 && f4.y<=370) {
        if (check_collision(personagem, f4)==0 && pulo!=0 && personagem.x+personagem.w<f4.x+f4.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=169 && personagem.y<=270 && f.y>=220 && f.y<=270) {
        if (check_collision(personagem, f)==0 && pulo!=0 && personagem.x+personagem.w<f.x+f.w && fds==0) {
            fds++;
            score+=100;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=169 && personagem.y<=270 && f1.y>=220 && f1.y<=270) {
        if (check_collision(personagem, f1)==0 && pulo!=0 && personagem.x+personagem.w<f1.x+f1.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=169 && personagem.y<=270 && f2.y>=220 && f2.y<=270) {
        if (check_collision(personagem, f2)==0 && pulo!=0 && personagem.x+personagem.w<f2.x+f2.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=169 && personagem.y<=270 && f3.y>=220 && f3.y<=270) {
        if (check_collision(personagem, f3)==0 && pulo!=0 && personagem.x+personagem.w<f3.x+f3.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
       if (personagem.y>=169 && personagem.y<=270 && f4.y>=220 && f4.y<=270) {
        if (check_collision(personagem, f4)==0 && pulo!=0 && personagem.x+personagem.w<f4.x+f4.w && fds==0) {
            score+=100;
            fds++;
            zzz=SDL_GetTicks();
        }
       }
    }
}

void comecar_novo () {
    lifes=4;
    playerInfo();
    pomo_voldemort_fireball();
    time=0, toques=0, toques_1=0, toques_2=0, toques_3=0;
    c_espada=0, pontuacao_final=0, score=0, bateu=0, bateu1=0, bateu2=0, bateu3=0, bateu4=0;
    subindo=0, frame=0, frame_voldemort=0, frame_sword=0;
    direita=0, direita1=0, direita2=0, direita3=0, direita4=0;
    esquerda=0, esquerda1=0, esquerda2=0, esquerda3=0, esquerda4=0;
    baixo=0, baixo1=0, baixo2=0, baixo3=0, baixo4=0;
    marcar=0, marcar1=0, marcar2=0, marcar3=0, marcar4=0;
    p_cima=0, p_baixo=0, fr=1;
    teclaBaixo=0, teclaCima=0, teclaDireita=0, teclaEspaco=0, teclaEsquerda=0;
}

void testar() {
    if (personagem.x>=0 && personagem.x<=80 && personagem.y>518 && personagem.y<522) {
        if (check_collision(personagem, f)==1) {
            f.x=85;
            f.y=541;
        } else if (check_collision(personagem, f1)==1) {
            f1.x=85;
            f1.y=541;
        } else if (check_collision(personagem, f2)==1) {
            f2.x=85;
            f2.y=541;
        } else if (check_collision(personagem, f3)==1) {
            f3.x=85;
            f3.y=541;
        } else if (check_collision(personagem, f4)==1) {
            f4.x=85;
            f4.y=541;
        }
    }
}

void bater_bola () {
    Mix_PauseMusic();
    playerInfo();
    t_espada=10000;c_espada=0;
    lifes--;
    //marcar=0, marcar1=0, marcar2=0, marcar3=0, marcar4=0;
    //bateu=0, bateu1=0, bateu2=0, bateu3=0, bateu4=0;
    Mix_PlayChannel(-1, colisao, 0);
    testar();
    if (lifes>0) {
        SDL_BlitSurface(perdeu_vida, 0, screen, 0);
        SDL_Flip(screen);
        SDL_Delay(3000);
    }
}

int main ( int argc, char** argv )
{

    inicializa();
    pomo_voldemort_fireball();
    Mix_PlayMusic(principal, 10);

    menu_principal:

    if (Mix_PlayingMusic()==-1) {
        Mix_PlayMusic(principal, 10);
    }
    jogoRodando=mostrarmenu(menu);
    if (jogoRodando==2) {
        jogoRodando=mostrarsimples(1);
        if (jogoRodando==2) {
            goto menu_principal;
        }
    } else if (jogoRodando==3) {
        jogoRodando=mostrarsimples(2);
        if (jogoRodando==2) {
            goto menu_principal;
        }
    } else if (jogoRodando==4) {
        jogoRodando=mostrarsimples(3);
        if (jogoRodando==2) {
            goto menu_principal;
        }
    } else if (jogoRodando==0) {
        return 0;
    }
    Mix_PauseMusic();
    Mix_PlayMusic(musica, 1);
    pontos = TTF_RenderText_Solid(t_1, "Score: ", textColor);
    vidas = TTF_RenderText_Solid(t_1, "Lifes: ", textColor);
    tempo_restante = TTF_RenderText_Solid(t_1, "Time ", textColor);
    tempo_espada = TTF_RenderText_Solid(t_1, "Sword: ", textColor);
    char c[5];
    t_restante = 300000;
    t_espada = 10000;
    iniciou = SDL_GetTicks();

    comecar:

    while(jogoRodando){

            start = SDL_GetTicks();
            if( Mix_PausedMusic() == 1 ) {
                Mix_ResumeMusic();
            }
            SDL_BlitSurface(background, 0, screen, 0);
            construir_plataformas();
            if (c_espada==0) {
                personagem.w=player.largura;
                if (teclaDireita==1) {
                    playerImage = IMG_Load("player.png");
                } else if (teclaEsquerda==1) {
                    playerImage = IMG_Load("player_1.png");
                }
            } else {
                personagem.w=player.larguraesp;
            }
            eventoTeclado();
            if (jogoRodando==0) {
                return 0;
            }
            personagem.x=player.dx;
            personagem.y=player.dy;
            personagem.h=player.altura;
            time++;
            firebola(time);
            mov_fireball();
            frame++;
            frame_sword++;
            condicao_fogo();
            sprintf(c, "%d", score);
            score_ = TTF_RenderText_Solid(t_1, c, textColor);
            sprintf(c, "%d", lifes-1);
            vidas_ = TTF_RenderText_Solid(t_1, c, textColor);
            if (f.x>80 && f.x<=120 && f.y==65) {
                frame_voldemort++;
            } else if (f1.x>80 && f1.x<=120 && f1.y==65) {
                frame_voldemort++;
            } else if (f2.x>80 && f2.x<=120 && f2.y==65) {
                frame_voldemort++;
            } else if (f3.x>80 && f3.x<=120 && f3.y==65) {
                frame_voldemort++;
            } else if (f4.x>80 && f4.x<=120 && f4.y==65) {
                frame_voldemort++;
            }
            if (frame_voldemort>=4) {
                frame_voldemort=0;
            }
            if (frame>=4) {
                frame=0;
            }
            if (frame_sword>1) {
                frame_sword=0;
            }
            if(player.sx > 180)
                player.sx = 0;

            if(player.sx < 0)
                player.sx = 180;

            if (player.sxesp>210)
                player.sxesp = 0;

            if (player.sxesp<0)
                player.sxesp=210;

            if(player.dx >= 730){
                player.dx = 730;
            }

            if(player.dx <= 0) {
                player.dx = 0;
            }
            if(player.dy >= 600){
                player.dy = 600;
            }

            if(player.dy <= 0){
                player.dy = 0;
            }
            if (player.up>55) {
                player.up = 0;
            }

            if (player.up<0) {
                player.up = 55;
            }

            SDL_Rect e;
            e.x = 200;
            e.y = 484;
            //Blitar a imagem na tela

            //SDL_BlitSurface(gold, 0, screen, &v[frame]);
            SDL_BlitSurface(escada, 0, screen, &e);

            e.x = 570;
            SDL_BlitSurface(escada_quebrada, 0, screen, &e);
            e.x = 350;
            e.y = 383;
            SDL_BlitSurface(escada, 0, screen, &e);
            e.x = 640;
            SDL_BlitSurface(escada_quebrada, 0, screen, &e);

            e.x = 84;
            e.y = 282;

            SDL_BlitSurface(escada, 0, screen, &e);
            e.x = 490;
            SDL_BlitSurface(escada_quebrada, 0, screen, &e);

            e.x = 730;
            e.y = 182;
            SDL_BlitSurface(escada, 0, screen, &e);

            e.x = 490;
            e.y = 2;
            SDL_BlitSurface(Pergaminho, 0, screen, &e);


            fontes.x = 525;
            fontes.y = 10;
            SDL_BlitSurface(pontos, 0, screen, &fontes);

            fontes.x = 623;
            SDL_BlitSurface(score_, 0, screen, &fontes);

            fontes.x = 680;
            SDL_BlitSurface(vidas, 0, screen, &fontes);

            fontes.x = 735;
            SDL_BlitSurface(vidas_, 0, screen, &fontes);

            fontes.x = 525;
            fontes.y = 36;
            SDL_BlitSurface(tempo_restante, 0, screen, &fontes);

            std::stringstream c_tempo;
            c_tempo<< "" << (t_restante - SDL_GetTicks()+iniciou)/60000;
            fontes.x = 590;
            minutos = TTF_RenderText_Solid( t_1, c_tempo.str().c_str(), textColor);
            SDL_BlitSurface(minutos, 0, screen, &fontes);

            if ((((t_restante - SDL_GetTicks()+iniciou)%60000)/1000)<10) {
                c_tempo <<": 0" << ((t_restante - SDL_GetTicks()+iniciou)%60000)/1000;
            } else {
                c_tempo <<":" << ((t_restante - SDL_GetTicks()+iniciou)%60000)/1000;
            }

            segundos = TTF_RenderText_Solid(t_1, c_tempo.str().c_str(), textColor);
            SDL_BlitSurface(segundos, 0, screen, &fontes);

            SDL_FreeSurface(minutos);
            SDL_FreeSurface(segundos);

            std::stringstream time_espada;
            fontes.x = 660;
            SDL_BlitSurface(tempo_espada, 0, screen, &fontes);
            if (c_espada>0) {
                time_espada <<" "<<((t_espada - SDL_GetTicks() + ttt)%60000/1000);
                if ((((t_espada-SDL_GetTicks()+ttt)%60000)/1000)<1) {
                    c_espada=0;
                }
            }
            fontes.x = 730;
            if (c_espada>0) {
                segundos = TTF_RenderText_Solid(t_1, time_espada.str().c_str(), textColor);
                SDL_BlitSurface(segundos, 0, screen, &fontes);
            } else {
                segundos = TTF_RenderText_Solid(t_1, "0", textColor);
                SDL_BlitSurface(segundos, 0, screen, &fontes);
            }

            draw_player(voldemort[frame_voldemort].x, voldemort[frame_voldemort].y, 40, 48, 50, 80, voldemort_s, screen);
            draw_player(Gina[frame].x, Gina[frame].y, 620, 110, 60, 60, Gina_s, screen );
            if (check_collision(personagem, esp_sword) && c_espada==0) {
                c_espada++;
                ttt=SDL_GetTicks();
            }
            if (c_espada==0) {
                draw_player(sword[frame_sword].x, sword[frame_sword].y, 550, 285, 21, 80, Espada, screen);
            }
            marcar_p_pulo();
            if (SDL_GetTicks()-zzz>5000) {
                fds=0;
                zzz=0;
            }

            if (fr>=1 && bateu==0) {
                draw_player(fogo.sx, fogo.sy, f.x, f.y, 30, 30, fireball, screen);
            }
            if (fr>=2 && bateu1==0) {
                draw_player(fogo_1.sx, fogo_1.sy, f1.x, f1.y, 30, 30, fireball, screen);
            }
            if (fr>=3 && bateu2==0) {
                draw_player(fogo_2.sx, fogo_2.sy, f2.x, f2.y, 30, 30, fireball, screen);
            }
            if (fr>=4 && bateu3==0) {
                draw_player(fogo_3.sx, fogo_3.sy, f3.x, f3.y, 30, 30, fireball, screen);
            }
            if (fr>=5 && bateu4==0) {
                draw_player(fogo_4.sx, fogo_4.sy, f4.x, f4.y, 30, 30, fireball, screen);
            }
            if (subindo) {
                draw_player(player.up, player.sy, player.dx, player.dy, player.largura, player.altura, player_subir, screen);
            } else if (c_espada==0){
                draw_player(player.sx, player.sy, player.dx, player.dy, player.largura, player.altura, playerImage, screen);
            } else if (c_espada>0) {
                draw_player(player.sxesp, player.sy, player.dx, player.dy, player.larguraesp, player.altura, player_sword, screen);
            }

            if (check_collision(personagem, g)==1 && time<200) {
                toques++;
            }

            if (check_collision(personagem, g_1)==1 && time<430) {
                toques_1++;
            }

            if (check_collision(personagem, g_2)==1 && time<700) {
                toques_2++;
            }

            if (check_collision(personagem, g_3)==1 && time<890) {
                toques_3++;
            }

            if (toques==1 || toques_1==1 || toques_2==1 || toques_3==1) {
                score+=150;
            }

            if (check_collision(personagem, f) && c_espada==1 && marcar==0) {
                score+=200;
                Mix_PlayChannel(-1, colisao, 0);
                bateu=1;
                marcar++;
            }

            if (check_collision(personagem, f1) && c_espada==1 && marcar1==0) {
                score+=200;
                Mix_PlayChannel(-1, colisao, 0);
                bateu1=1;
                marcar1++;
            }

            if (check_collision(personagem, f2) && c_espada==1 && marcar2==0) {
               score+=200;
               Mix_PlayChannel(-1, colisao, 0);
               bateu2=1;
               marcar2++;
            }

            if (check_collision(personagem, f3) && c_espada==1 && marcar3==0) {
                score+=200;
                Mix_PlayChannel(-1, colisao, 0);
                bateu3=1;
                marcar3++;
            }

            if (check_collision(personagem, f4) && c_espada==1 && marcar4==0) {
                score+=200;
                Mix_PlayChannel(-1, colisao, 0);
                bateu4=1;
                marcar4++;
            }

            //checar_colisao_bolas();

            if (time<200 && toques==0) {
                draw_player(v[frame].x, v[frame].y, g.x, g.y, 50, 28, gold, screen);
            }

            if (time<430 && toques_1==0) {
                draw_player(v[frame].x, v[frame].y, g_1.x, g_1.y, 50, 28, gold, screen);
            }

            if (time<700 && toques_2==0) {
                draw_player(v[frame].x, v[frame].y, g_2.x, g_2.y, 50, 28, gold, screen);
            }

            if (time<890 && toques_3==0) {
                draw_player(v[frame].x, v[frame].y, g_3.x, g_3.y, 50, 28, gold, screen);
            }
            // colisão
            if (check_collision(personagem, f) && bateu==0 && c_espada==0) {
                bater_bola();
                if (lifes>0) {
                    goto comecar;
                }
            }
            if (check_collision(personagem, f1) && bateu1==0 && c_espada==0) {
                bater_bola();
                if (lifes>0) {
                    goto comecar;
                }
            }
            if (check_collision(personagem, f2) && bateu2==0 && c_espada==0) {
                bater_bola();
                if (lifes>0) {
                    goto comecar;
                }
            }
            if (check_collision(personagem, f3) && bateu3==0 && c_espada==0) {
                bater_bola();
                if (lifes>0) {
                    goto comecar;
                }
            }
            if (check_collision(personagem, f4) && bateu4==0 && c_espada==0) {
                bater_bola();
                if (lifes>0) {
                    goto comecar;
                }
            }

            if (check_collision(personagem, snake)) {
                Mix_PauseMusic();
                pontuacao_final=score;
                t_restou=t_restante - SDL_GetTicks()+iniciou;
                pontuacao_final+=(int) t_restou/1000;
                jogoRodando=mostrarganho(ganhou);
                if (jogoRodando==2) {
                    comecar_novo();
                    iniciou=SDL_GetTicks();
                    goto menu_principal;
                } else if (jogoRodando==1) {
                    comecar_novo();
                    iniciou=SDL_GetTicks();
                    goto comecar;
                } else if (jogoRodando==0) {
                    return 0;
                }
            }

            if (lifes==0) {
                Mix_PauseMusic();
                SDL_Delay(2000);
                jogoRodando=mostrarperder(game_over);
                iniciou=SDL_GetTicks();
                if (jogoRodando==1) {
                    Mix_PlayMusic(musica, 1);
                    comecar_novo();
                    goto comecar;
                } else if (jogoRodando==2) {
                    jogoRodando=1;
                    comecar_novo();
                    goto menu_principal;
                } else if (jogoRodando==0) {
                    return 0;
                }
            }

        //Atualiza a tela
            if(1000/FPS >(SDL_GetTicks()-start))
                SDL_Delay(1000/FPS-(SDL_GetTicks()-start));

            SDL_Flip( screen);

            if(SDL_Flip(screen) == -1){
                return 1;
            }

    }
    //Liberar imagem carregada
    liberar();
    //Encerra o SDL
    SDL_Quit();
    return 0;
}
