#include "dominios.h"
#include "entidades.h"
#include "database.h"
#include "controladores.h"

using namespace std;

int main () {

    BancoDeDados                db;
    UserController              uController;
    MatchController             mController;
    try {
        db.reconstruir();
        uController.menu(db, mController);
        db.salvarTudo();
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}