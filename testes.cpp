#include "testes.h"

void TUCodigoJogo::testar ()
{
    try {
        codigo.setar(valorValido);

        if (codigo.get() != valorValido)
            estado = FALHA;
    } catch(invalid_argument excecao) {
        estado = FALHA;
    }
}

int TUCodigoJogo::run ()
{
    testar();
    return estado;
}


void TUCodigoIngresso::testar ()
{
    try {
        codigo.setar(valorValidoUns);
        if (codigo.get() != valorValidoUns)
            estado = FALHA;
        if (codigo.getString() != valorValidoStr)
            estado = FALHA;
    } catch(invalid_argument excecao) {
        estado = FALHA;
    }
}

int TUCodigoIngresso::run ()
{
    testar();
    return estado;
}


void TUNomeDoJogo::testar ()
{
    try {
        nome.setar(valorValido);

        if (nome.get() != valorValido)
            estado = FALHA;
    } catch(invalid_argument excecao) {
        estado = FALHA;
    }
}

int TUNomeDoJogo::run ()
{
    testar();
    return estado;
}


void TUHorario::testar ()
{
    try {
        horario.setar(valorValidoHora, valorValidoMin);

        unsigned short testeH, testeM;
        horario.get(&testeH, &testeM);

        if (testeH != valorValidoHora || testeM != valorValidoMin)
            estado = FALHA;
    } catch(invalid_argument excecao) {
        estado = FALHA;
    }
}

int TUHorario::run ()
{
    testar();
    return estado;
}


void TUPreco::testar ()
{
    try {
        preco.setar(valorValido);

        if (preco.get() != valorValido)
            estado = FALHA;
    } catch(invalid_argument excecao) {
        estado = FALHA;
    }
}

int TUPreco::run ()
{
    testar();
    return estado;
}


void TUNumeroSala::testar ()
{
    try {
        numero.setar(valorValido);

        if (numero.get() != valorValido)
            estado = FALHA;
    } catch(invalid_argument excecao) {
        estado = FALHA;
    }
}

int TUNumeroSala::run ()
{
    testar();
    return estado;
}


void TUCidade::testar ()
{
    try {
        cidade.setar(valorValido);

        if (cidade.get() != valorValido)
            estado = FALHA;
    } catch(invalid_argument excecao) {
        estado = FALHA;
    }
}

int TUCidade::run ()
{
    testar();
    return estado;
}


void TUEstado::testar ()
{
    try {
        estadoClasse.setar(valorValido);

        if (estadoClasse.getString() != valorValido)
            estado = FALHA;
    } catch(invalid_argument excecao) {
        estado = FALHA;
    }
}

int TUEstado::run ()
{
    testar();
    return estado;
}


void TUDisponibilidade::testar ()
{
    try {
        disp.setar(valorValido);

        if (disp.get() != valorValido)
            estado = FALHA;
    } catch(invalid_argument excecao) {
        estado = FALHA;
    }
}

int TUDisponibilidade::run ()
{
    testar();
    return estado;
}


void TUTipoJogo::testar ()
{
    try {
        tipo.setar(valorValido);

        if (tipo.get() != valorValido)
            estado = FALHA;
    } catch(invalid_argument excecao) {
        estado = FALHA;
    }
}

int TUTipoJogo::run ()
{
    testar();
    return estado;
}


void TUCpf::testar ()
{
    try {
        cpf.setar(valorValido);

        if (cpf.get() != valorValido)
            estado = FALHA;
    } catch(invalid_argument excecao) {
        estado = FALHA;
    }
}

int TUCpf::run ()
{
    testar();
    return estado;
}


void TUSenha::testar ()
{
    try {
        senha.setar(valorValido);

        if (senha.get() != valorValido)
            estado = FALHA;
    } catch(invalid_argument excecao) {
        estado = FALHA;
    }
}

int TUSenha::run ()
{
    testar();
    return estado;
}


void TUEstadio::testar ()
{
    try {
        estadio.setar(valorValido);

        if (estadio.get() != valorValido)
            estado = FALHA;
    } catch(invalid_argument excecao) {
        estado = FALHA;
    }
}

int TUEstadio::run ()
{
    testar();
    return estado;
}


void TUData::testar ()
{
    try {
        data.setar(valorValidoAno, valorValidoMes, valorValidoDia);

        if (data.getAno() != valorValidoAno || data.getMes() != valorValidoMes || data.getDia() != valorValidoDia)
            estado = FALHA;
    } catch(invalid_argument excecao) {
        estado = FALHA;
    }
}

int TUData::run ()
{
    testar();
    return estado;
}
