/* 
 * File:   main.cpp
 * Author: jeferson
 *
 * Created on August 31, 2014, 9:20 AM
 */

#include <iup/iup.h>
#include <iup/iupgl.h>
#include <cstdio>
#include "MainWindow.h"


/**
 * Funcao princial.
 * @param argc - numero de argumentos do programa.
 * @param argv - lista de argumentos.
 * @return - 0 caso tenha havido sucesso e 1 caso contrario.
 */
int main( int argc, char** argv )
{
    //Inicializa a IUP.
    IupOpen( &argc, &argv );
    
    //Inicializa a OpenGL na IUP.
    IupGLCanvasOpen();
    
    //Cria objeto.
    MainWindow *window = new MainWindow();

    printf("IUP: %s\n", IupVersion());
        
    //Exibe a janela.
    window->show();
    
    //Coloca a IUP em loop.
    IupMainLoop();
    
    //Deleta o obejto alocado.
    delete window;
    
    //Fecha a IUP.
    IupClose();
    
    return 0;
}

