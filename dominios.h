#ifndef DOMINIOS_H_INCLUDED
#define DOMINIOS_H_INCLUDED

#include <bits/stdc++.h>

using namespace std;

/**** Dominios ****/

class DadoString {
   protected:
      virtual void         validar (string) throw (invalid_argument)=0;
   
   public:
      virtual void         setar (string) =0;

};


class CodigoJogo : public DadoString {
   private:
      string               numero;
      const short          size {3};
      void                 validar (string input) throw (invalid_argument);

   public:
      void                 setar (string input);
      string               get () const;
      CodigoJogo&          operator=(const CodigoJogo& outro);
};

class CodigoIngresso {
   private:
      unsigned             numero;
      const unsigned       maxSize {99999};
      void                 validar (unsigned input) throw (invalid_argument);

   public:
      void                 setar (unsigned input);
      unsigned             get ();
      string               getString ();
};

class NomeDoJogo : public DadoString {
   private:
      string               nome;
      const short          maxSize {24};
      void                 validar (string input) throw (invalid_argument);

   public:
      void                 setar (string input);
      string               get () const;
};

// Usar time_t para lidar com data


class Horario {
   private:
      unsigned short       hora;
      unsigned short       minuto;
      void                 validar (unsigned short hora, unsigned short minuto) throw (invalid_argument);
   
   public:
      void                 setar (unsigned short hora, unsigned short minuto);
      void                 get (unsigned short* output_0, unsigned short* output_1) const;
      Horario&             operator= (const Horario& outro);
};

class Preco {
   private:
      float                valor;
      const float          max {1000};
      void                 validar (float preco) throw (invalid_argument);

   public:
      void                 setar (float preco);
      float                get () const;
};

class NumeroSala {
   private:
      unsigned             valor;
      const short          min {1};
      const short          max {10};
      void                 validar (unsigned num) throw (invalid_argument);

   public:
      void                 setar (unsigned num);
      unsigned             get ();
};

class Cidade : public DadoString {
   private:
      string               nome;
      const short          maxSize {16};
      void                 validar (string cidade) throw (invalid_argument);

   public:
      void                 setar (string cidade);
      string               get () const;
};

enum class                 Sigla { AC, AL, AP, AM, BA, CE, DF, ES, GO, MA,
   MT, MS, MG, PA, PB, PR, PE, PI, RJ, RN, RS, RO, RR, SC, SP, SE, TO };

class Estado {
   private:
      Sigla                sigla;
      map<string, Sigla>   stringParaSigla;
      map<Sigla, string>   siglaParaString;
      void                 validar (string input) throw (invalid_argument);               

   public:
      Estado ();
      void                 setar (string input);
      Sigla                getSigla () const;
      string               getString () const;
      Estado&              operator= (const Estado& outro);
};


class Disponibilidade {
   private:
      unsigned             valor;
      const unsigned       max {250};
      void                 validar (unsigned disp) throw (invalid_argument);

   public:
      void                 setar (unsigned disp);
      unsigned             get ();
      unsigned             getMaxDisp () { return max; };
};

class TipoJogo {
   private:
      unsigned             valor;
      const short          min {1};
      const short          max {4};
      void                 validar (unsigned tipo) throw (invalid_argument);

   public:
      void                 setar (unsigned tipo);
      unsigned             get () const;
      string               getString ();
};

class Cpf {
   private:
      string               valor;
      const short          maxSize {11};
      void                 validar (string cpf) throw (invalid_argument);

   public:
      void                 setar (string cpf);
      string               get () const;
      bool                 operator== (const Cpf& outro);
      Cpf&                 operator= (const Cpf& outro);
};

class Senha {
   private:
      string               valor;
      const short          size {6};
      void                 validar (string senha) throw (invalid_argument);

   public:
      void                 setar (string senha);
      string               get () const;
};

class Estadio {
   private:
      string               nome;
      const short          maxSize {25};
      void                 validar (string nome) throw (invalid_argument);

   public:
      void                 setar (string nome);
      string               get () const;
};

class Data {
   private:
      int                  ano;
      int                  mes;
      int                  dia;
      void                 validar (int ano, int mes, int dia) throw (invalid_argument);

      public:
         void              setar (int ano, int mes, int dia);
         int               getAno() const;
         int               getMes() const;
         int               getDia() const;
         Data&             operator=(const Data& outro);
};

#endif