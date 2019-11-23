// Universidade de Brasília - Ciência da Computação
// Técnicas de Programação 1 - 2º/2019
// Prof. Washington
// Marco
// Rafael

// Mudanças:
// - Adicionada classe virtual "DadoString".
// - Classe "Banco de dados" transformada em Singleton.
// - Criados testes-fumaça.

#include "dominios.h"
#include "entidades.h"
#include "database.h"
#include "controladores.h"

using namespace std;

int main () {

    BancoDeDados*               DB = &BancoDeDados::getInstance();
    UserController              uController;
    MatchController             mController;
    DB->reconstruir();
    uController.menu(*DB, mController);
    DB->salvarTudo();
    

    return 0;
}