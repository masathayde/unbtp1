#include "dominios.h"

void CodigoJogo::validar (string input) throw (invalid_argument)
{
    if (input.size() != this->size)
        throw invalid_argument("Erro: Tamanho incorreto");

    for (auto it : input) {
        if (it < '0' || it > '9')
            throw invalid_argument("Erro: Carater invalido");
    }
}

void CodigoJogo::setar (string input)
{
    this->validar(input);
    this->numero = input;
}

string CodigoJogo::get () const
{
    return this->numero;
}

CodigoJogo& CodigoJogo::operator=(const CodigoJogo& outro)
{
    this->numero = outro.get();
    return *this;
}

//------

void CodigoIngresso::validar (unsigned input) throw (invalid_argument)
{
    if (input > maxSize)
        throw invalid_argument("Erro: Codigo invalido");
}

void CodigoIngresso::setar (unsigned input)
{
    this->validar(input);
    this->numero = input;
}

unsigned CodigoIngresso::get ()
{
    return this->numero;
}

string CodigoIngresso::getString ()
{
    stringstream ss;
    ss << setw(5) << setfill('0') << this->numero;
    return ss.str();
}

//------

void NomeDoJogo::validar (string input) throw (invalid_argument)
{
    if (input.size() > this->maxSize)
        throw invalid_argument("Erro: Nome invalido - Tamanho excedido");

    int charCount = 0;
    char previousChar = '0';

    for (auto it : input) {
        if (it < '0' || it > '9')
            charCount++;

        if (previousChar == ' ' && it == ' ')
            throw invalid_argument("Erro: Nome invalido - Mais de dois espacos");

        previousChar = it;
    }

    if (charCount == 0)
        throw invalid_argument("Erro: Nome invalido - Nenhuma letra");
}

void NomeDoJogo::setar (string input)
{
    this->validar(input);
    this->nome = input;
}

string NomeDoJogo::get () const
{
    return this->nome;
}

//------

void Horario::validar (unsigned short hora, unsigned short minuto) throw (invalid_argument)
{
    if (hora < 7 || hora > 22)
        throw invalid_argument("Erro: Horario invalido");
    if (minuto > 45 || minuto % 15 != 0)
        throw invalid_argument("Erro: Horario invalido");
}

void Horario::setar (unsigned short h, unsigned short m)
{
    this->validar(h, m);
    this->hora = h;
    this->minuto = m;
}


void Horario::get (unsigned short* h, unsigned short* m) const
{
    *h = this->hora;
    *m = this->minuto;
}

Horario& Horario::operator= (const Horario& outro)
{
    unsigned short _hora, _min;
    outro.get(&_hora, &_min);
    this->setar(_hora, _min);
    return *this;
}

//------

void Preco::validar (float preco) throw (invalid_argument)
{
    if (preco < 0 || preco > max)
        throw invalid_argument("Erro: preco invalido");

}

void Preco::setar (float preco)
{
    this->validar(preco);
    this->valor = preco;
}

float Preco::get () const
{
    return this->valor;
}

//------

void NumeroSala::validar (unsigned sala) throw (invalid_argument)
{
    if (sala < this->min || sala > this->max)
        throw invalid_argument("Erro: sala invalida");
}

void NumeroSala::setar (unsigned num)
{
    this->validar(num);
    this->valor = num;
}

unsigned NumeroSala::get ()
{
    return this->valor;
}

//------

void Cidade::validar (string input) throw (invalid_argument)
{
    if (input.size() > this->maxSize)
        throw invalid_argument("Erro: Tamanho maximo excedido");

    char previousChar = ' ';

    for (auto it : input) {
        if (it >= '0' && it <= '9')
            throw invalid_argument("Erro: Numeros nao sao permitidos");

        if (previousChar == ' ' && (it == ' ' || it == '.' ) )
            throw invalid_argument("Erro: sequencia invalida");
        
        previousChar = it;
    }

}

void Cidade::setar (string input)
{
    this->validar(input);
    this->nome = input;
}

string Cidade::get () const
{
    return this->nome;
}

//------

void Disponibilidade::validar (unsigned input) throw (invalid_argument)
{
    if (input > this->max)
        throw invalid_argument("Erro: valor invalido");
}

void Disponibilidade::setar (unsigned disp)
{
    this->validar(disp);
    this->valor = disp;
}

unsigned Disponibilidade::get ()
{
    return this->valor;
}

//------

void TipoJogo::validar (unsigned tipo) throw (invalid_argument)
{
    if (tipo < min || tipo > max)
        throw invalid_argument("Erro: Tipo invalido");
}

void TipoJogo::setar (unsigned tipo)
{
    this->validar(tipo);
    this->valor = tipo;
}

unsigned TipoJogo::get () const
{
    return this->valor;
}

string TipoJogo::getString ()
{
    switch(this->valor) {
        case 1: return "LOCAL";
        case 2: return "ESTADUAL";
        case 3: return "NACIONAL";
        case 4: return "INTERNACIONAL";
    }
}

//------

void Cpf::validar (string input) throw (invalid_argument)
{
    // Lembrando de subtrair '0' quando converter char para int

    if (input.size() > this->maxSize)
        throw invalid_argument("Erro: CPF invalido");

    int ver0, ver1;
    ver0 = 0;
    ver1 = 0;

    char rptChar = input[0];
    bool repeat = true;

    for (int i = 0; i < input.size() - 2; i++) {
        if (input[i] != rptChar)
            repeat = false;

        if (input[i] < '0' || input[i] > '9')
            throw invalid_argument("Erro: CPF invalido");

        ver0 += (10 - i) * (input[i] - '0');
        ver1 += (11 - i) * (input[i] - '0');
    }

    if (repeat)
        throw invalid_argument("Erro: CPF invalido");

    // 1o digito
    ver0 = ver0 % 11;
    if (ver0 < 2)
        ver0 = 0;
    else
        ver0 = 11 - ver0;

    if (input[9] - '0' != ver0)
        throw invalid_argument("Erro: CPF invalido");

    // 2o digito
    ver1 += ver0*2;
    ver1 = ver1 % 11;
    if (ver1 < 2)
        ver1 = 0;
    else
        ver1 = 11 - ver1;

    if (input[10] - '0' != ver1)
        throw invalid_argument("Erro: CPF invalido");
}

void Cpf::setar (string input)
{
    this->validar(input);
    this->valor = input;
}

string Cpf::get () const
{
    return this->valor;
}

bool Cpf::operator== (const Cpf& outro)
{
    return this->get() == outro.get();
}

Cpf& Cpf::operator= (const Cpf& outro)
{
    valor = outro.get();
    return *this;
}

//------

void Senha::validar (string input) throw (invalid_argument)
{
    if (input.size() != this->size)
        throw invalid_argument("Erro: Senha invalida");

    char previousChar = 0;
    bool upperCase = false;
    bool lowerCase = false;
    bool number = false;

    for (auto it : input) {
        if (it == previousChar)
            throw invalid_argument("Erro: Senha invalida");

        if (it >= '0' && it <= '9')
            number = true;
        else if (it >= 'A' && it <= 'Z')
            upperCase = true;
        else if (it >= 'a' && it <= 'z')
            lowerCase = true;
        else
            throw invalid_argument("Erro: Senha invalida");

        previousChar = it;
    }

    if (!upperCase || !lowerCase || !number)
        throw invalid_argument("Erro: Senha invalida");

}

void Senha::setar (string input)
{
    this->validar(input);
    this->valor = input;
}

string Senha::get () const
{
    return this->valor;
}

// --------

void Estadio::validar (string input) throw (invalid_argument)
{
    if (input.size() > this->maxSize)
        throw invalid_argument("Erro: Tamanho maximo excedido");

    int charCount = 0;
    char previousChar = '0';

    for (auto it : input) {
        if (it < '0' || it > '9')
            charCount++;

        if (previousChar == ' ' && it == ' ')
            throw invalid_argument("Erro: Mais de um espaco em seguida");

        previousChar = it;
    }

    if (charCount == 0)
        throw invalid_argument("Erro: Nenhuma letra no nome");

}

void Estadio::setar (string input)
{
    this->validar(input);
    this->nome = input;
}

string Estadio::get () const
{
    return nome;
}

// ---------

void Data::validar (int ano, int mes, int dia) throw (invalid_argument)
{
    if (ano < 0 || ano > 99)
        throw invalid_argument("Erro: Data invalida");

    if (mes < 1 || mes > 12)
        throw invalid_argument("Erro: Data invalida");

    if (dia < 1 || dia > 31)
        throw invalid_argument("Erro: Data invalida");


    bool anoBissexto = false;
    ano += 2000;

    if ( (ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0 )
        anoBissexto = true;


    // Teste de dias invalidos meus deus que coisa mais chata

    if (mes <= 7 && mes % 2 == 0 && dia > 30)
        throw invalid_argument("Erro: Data invalida");

    if (mes >= 8 && mes % 2 == 1 && dia > 30)
        throw invalid_argument("Erro: Data invalida");

    if (mes == 2 && dia > 29)
        throw invalid_argument("Erro: Data invalida");

    if (mes == 2 && !anoBissexto && dia > 28)
        throw invalid_argument("Erro: Data invalida");
}

void Data::setar (int ano, int mes, int dia)
{
    this->validar(ano, mes, dia);
    this->ano = ano;
    this->mes = mes;
    this->dia = dia;
}

int Data::getAno () const
{
    return ano;
}

int Data::getMes () const
{
    return mes;
}

int Data::getDia () const
{
    return dia;
}

Data& Data::operator= (const Data& outro)
{
    ano = outro.getAno();
    mes = outro.getMes();
    dia = outro.getDia();
    return *this;
}

// --------

Estado::Estado ()
{
    // Popular mapa
    // Adoro programar :) !!!
    stringParaSigla.insert(pair<string, Sigla>("ac", Sigla::AC));
    stringParaSigla.insert(pair<string, Sigla>("AC", Sigla::AC));
    stringParaSigla.insert(pair<string, Sigla>("al", Sigla::AL));
    stringParaSigla.insert(pair<string, Sigla>("AL", Sigla::AL));
    stringParaSigla.insert(pair<string, Sigla>("ap", Sigla::AP));
    stringParaSigla.insert(pair<string, Sigla>("AP", Sigla::AP));
    stringParaSigla.insert(pair<string, Sigla>("am", Sigla::AM));
    stringParaSigla.insert(pair<string, Sigla>("AM", Sigla::AM));
    stringParaSigla.insert(pair<string, Sigla>("ba", Sigla::BA));
    stringParaSigla.insert(pair<string, Sigla>("BA", Sigla::BA));
    stringParaSigla.insert(pair<string, Sigla>("ce", Sigla::CE));
    stringParaSigla.insert(pair<string, Sigla>("CE", Sigla::CE));
    stringParaSigla.insert(pair<string, Sigla>("df", Sigla::DF));
    stringParaSigla.insert(pair<string, Sigla>("DF", Sigla::DF));
    stringParaSigla.insert(pair<string, Sigla>("es", Sigla::ES));
    stringParaSigla.insert(pair<string, Sigla>("ES", Sigla::ES));
    stringParaSigla.insert(pair<string, Sigla>("go", Sigla::GO));
    stringParaSigla.insert(pair<string, Sigla>("GO", Sigla::GO));
    stringParaSigla.insert(pair<string, Sigla>("ma", Sigla::MA));
    stringParaSigla.insert(pair<string, Sigla>("MA", Sigla::MA));
    stringParaSigla.insert(pair<string, Sigla>("mt", Sigla::MT));
    stringParaSigla.insert(pair<string, Sigla>("MT", Sigla::MT));
    stringParaSigla.insert(pair<string, Sigla>("ms", Sigla::MS));
    stringParaSigla.insert(pair<string, Sigla>("MS", Sigla::MS));
    stringParaSigla.insert(pair<string, Sigla>("mg", Sigla::MG));
    stringParaSigla.insert(pair<string, Sigla>("MG", Sigla::MG));
    stringParaSigla.insert(pair<string, Sigla>("pa", Sigla::PA));
    stringParaSigla.insert(pair<string, Sigla>("PA", Sigla::PA));
    stringParaSigla.insert(pair<string, Sigla>("pb", Sigla::PB));
    stringParaSigla.insert(pair<string, Sigla>("PB", Sigla::PB));
    stringParaSigla.insert(pair<string, Sigla>("pr", Sigla::PR));
    stringParaSigla.insert(pair<string, Sigla>("PR", Sigla::PR));
    stringParaSigla.insert(pair<string, Sigla>("pe", Sigla::PE));
    stringParaSigla.insert(pair<string, Sigla>("PE", Sigla::PE));
    stringParaSigla.insert(pair<string, Sigla>("pi", Sigla::PI));
    stringParaSigla.insert(pair<string, Sigla>("PI", Sigla::PI));
    stringParaSigla.insert(pair<string, Sigla>("rj", Sigla::RJ));
    stringParaSigla.insert(pair<string, Sigla>("RJ", Sigla::RJ));
    stringParaSigla.insert(pair<string, Sigla>("rn", Sigla::RN));
    stringParaSigla.insert(pair<string, Sigla>("RN", Sigla::RN));
    stringParaSigla.insert(pair<string, Sigla>("rs", Sigla::RS));
    stringParaSigla.insert(pair<string, Sigla>("RS", Sigla::RS));
    stringParaSigla.insert(pair<string, Sigla>("ro", Sigla::RO));
    stringParaSigla.insert(pair<string, Sigla>("RO", Sigla::RO));
    stringParaSigla.insert(pair<string, Sigla>("rr", Sigla::RR));
    stringParaSigla.insert(pair<string, Sigla>("RR", Sigla::RR));
    stringParaSigla.insert(pair<string, Sigla>("sc", Sigla::SC));
    stringParaSigla.insert(pair<string, Sigla>("SC", Sigla::SC));
    stringParaSigla.insert(pair<string, Sigla>("sp", Sigla::SP));
    stringParaSigla.insert(pair<string, Sigla>("SP", Sigla::SP));
    stringParaSigla.insert(pair<string, Sigla>("se", Sigla::SE));
    stringParaSigla.insert(pair<string, Sigla>("SE", Sigla::SE));
    stringParaSigla.insert(pair<string, Sigla>("to", Sigla::TO));
    stringParaSigla.insert(pair<string, Sigla>("TO", Sigla::TO));

    siglaParaString.insert(pair<Sigla, string>(Sigla::AC, "AC"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::AL, "AL"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::AP, "AP"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::AM, "AM"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::CE, "CE"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::DF, "DF"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::ES, "ES"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::GO, "GO"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::MA, "MA"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::MT, "MT"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::MS, "MS"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::MG, "MG"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::PA, "PA"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::PB, "PB"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::PR, "PR"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::PE, "PE"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::PI, "PI"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::RJ, "RJ"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::RN, "RN"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::RO, "RO"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::RR, "RR"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::SC, "SC"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::SP, "SP"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::SE, "SE"));
    siglaParaString.insert(pair<Sigla, string>(Sigla::TO, "TO"));
}

void Estado::validar (string input) throw (invalid_argument)
{
    if (stringParaSigla.find(input) == stringParaSigla.end())
        throw invalid_argument("Erro: Sigla invalida");
}

void Estado::setar (string input)
{
    this->validar(input);
    this->sigla = this->stringParaSigla[input];
}

Sigla Estado::getSigla () const
{
    return this->sigla;
}

string Estado::getString () const
{
    return siglaParaString.find(sigla)->second;
}

Estado& Estado::operator=(const Estado& outro)
{
    this->sigla = outro.getSigla();
    return *this;
}
