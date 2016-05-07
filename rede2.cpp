#include <iostream>       // std::cout
#include <string>         // std::string
#include <stdlib.h>

#define BLUE "\e[34m"
#define RED "\e[31m"
#define CLEAR "\033[0m"
#define GREEN "\e[92m"

using namespace std;

bool verify(int num ){
  if(num==0 || num == 128 || num == 192 || num == 224 || num == 240 || num == 248 || num == 252 || num == 254 || num == 255){
    return true;
  }
  return false;
}
bool verify2(int num){
  if(num < 0 || num > 255){
    return false;
  }
  return true;
}
int verify3(int num){
  if(num ==0){
    num=0;
  }
  if(num == 128)
    num=1;
  if(num == 192)
    num=2;
  if(num == 224)
    num=3;
  if(num == 240)
    num=4;
  if(num == 248)
    num=5;
  if(num == 252)
    num=6;
  if(num == 254)
    num=7;
  if(num == 255)
    num= 8;
  return num;
}

int classCheck(string str3,string str4,string str5,string str6){
   int intMask1 = std::stoi( str3 ); 
   int intMask2 = std::stoi (str4);
   int intMask3 = std::stoi( str5 ); 
   int intMask4 = std::stoi (str6);
   int bit = verify3(intMask1) + verify3(intMask2) + verify3(intMask3) + verify3(intMask4);

   if(verify(intMask1) != 1 || verify(intMask2) != 1 || verify(intMask3) != 1 || verify(intMask4) != 1){
     std::cout<<"Mascara inválida (numeros não correspondem aos possiveis valores),abortando"<<'\n';
     exit(EXIT_SUCCESS);
   }
   return bit;
}
int blockCheck(int num){
  if(num > 32 && num < 0){
    std::cout<<"Mascara inválida(número não pertence ao alcance da máscara)"<<'\n';
    exit(EXIT_SUCCESS);
  }
  return num;  
}
int checkMask(string mask){ //função para converter a máscara em blocos para a máscara em classe DO ÚLTIMO BLOCO DA MÁSCARA
  
  //string mask;
  string dot=".";
  string bar="/";
  
  std::cout<<"Insira sua mascara: ";
  
  std::getline(std::cin,mask);
    std::string str3; //primeiro octeto do ip
    std::string str4; // segundo octeto do ip
    std::string str5; //terceiro octeto do ip
    std::string str6; //quarto octeto do ip

    std::size_t found = mask.find(dot); //elemento que vai procurar o . nas strings
    int check = 0; //Verificador de caso seja no modo em classes
    int check2=0; //Verificador de caso seja no modo em blocos

    int val=0;//valor a ser retornado

    if (found!=std::string::npos){
      check++;
      //std::cout << "first 'dot' found at: " << found << '\n';
    }
    str3 = mask.substr (0,found); //primeira string sendo definida até o primeiro ponto
    int aux1=found; //auxiliar para definir a posicao do ponto 1

    found=mask.find(".",found+1); //atualizando o procurador 
    if (found!=std::string::npos){
      check++;
      //std::cout << "second 'dot' found at: " << found << '\n';
    }
    int whatever = found - aux1-1; //diferença entre o ponto atual e o ponto anterior
    str4 = mask.substr (aux1+1,whatever);//segunda string sendo definida até o segundo ponto
    int aux2=found; //auxiliar para definir a posicao do ponto 2

    found=mask.find(".",found+1); //atualizando o procurador 
    if (found!=std::string::npos){
      check++;
      //std::cout << "third 'dot' found at: " << found << '\n';
    }
    int whatever2 = found - aux2-1; //diferença entre o ponto atual e o ponto anterior
    str5 = mask.substr (aux2+1,whatever2); //terceira string sendo definida até o terceiro ponto

    str6 = mask.substr (found+1); //quarta string do terceiro ponto até o fim

    found=mask.find(".",found+1);//checando se não há 4 pontos
    if (found!=std::string::npos){
      check++;    
    }

    found=mask.find("/",found+1);
    if (found!=std::string::npos){
      check2++;    
    }

    if(check2== 1 && check == 3){ //Caso tenha 3 pontos e uma barra na mascara
     std::cout<<"Nem vem ¬¬"<<'\n';
      exit(EXIT_SUCCESS);
    }
    if(check == 3){ //Caso haja 3 pontos
      val=classCheck(str3,str4,str5,str6);
      //return val;
    }
    if(check2 == 1){//Caso haja uma barra
      val = std::stoi(mask);
      val= blockCheck(val);
      //return val;
    }
    if(check != 3 && check2 != 1){//Caso nao haja nem 3 pontos nem uma barra
      std::cout<<"Mascara inválida"<<'\n';
      exit(EXIT_SUCCESS);
    }
    return val;
}



int main ()
{
  std::string str;// ("192.168.7.2"); //ip do usuario
  std::string str2 ("."); //string a ser procurada
  std::string str3; //primeiro octeto do ip
  std::string str4; // segundo octeto do ip
  std::string str5; //terceiro octeto do ip
  std::string str6; //quarto octeto do ip
  std::string mask; //("255.255.255.0");
  int check=0;

  std::cout<<"Insira seu IP: ";
  std::getline(std::cin,str);
  if(str=="127.0.0.0"){
    std::cout<<"Está é uma rede reservada para loopback!"<<endl;
    exit(EXIT_SUCCESS);
  }
  //std::cout<<"Insira sua mascara: ";
  //std::getline(std::cin,mask);

  int numMask=checkMask(mask);

  // different member versions of find in the same order as above:
  std::size_t found = str.find(str2); //elemento que vai procurar o . nas strings
  if (found!=std::string::npos){
    check++;
    //std::cout << "first 'dot' found at: " << found << '\n';
  }
  str3 = str.substr (0,found); //primeira string sendo definida até o primeiro ponto
  int aux1=found; //auxiliar para definir a posicao do ponto 1

  found=str.find(".",found+1); //atualizando o procurador 
  if (found!=std::string::npos){
    check++;
    //std::cout << "second 'dot' found at: " << found << '\n';
  }
  int whatever = found - aux1-1; //diferença entre o ponto atual e o ponto anterior
  str4 = str.substr (aux1+1,whatever);//segunda string sendo definida até o segundo ponto
  int aux2=found; //auxiliar para definir a posicao do ponto 2

  found=str.find(".",found+1); //atualizando o procurador 
  if (found!=std::string::npos){
    check++;
    //std::cout << "third 'dot' found at: " << found << '\n';
  }
  int whatever2 = found - aux2-1; //diferença entre o ponto atual e o ponto anterior
  str5 = str.substr (aux2+1,whatever2); //terceira string sendo definida até o terceiro ponto

  str6 = str.substr (found+1); //quarta string do terceiro ponto até o fim

  if(check != 3){
     std::cout<<"IP inválido(quantidade de octetos errada),abortando"<<'\n';
     exit(EXIT_SUCCESS);
  }

    //transformacoes das strings para inteiros
  int myint = std::stoi( str3 ); 
  int myint2 = std::stoi (str4);
  int myint3 = std::stoi( str5 ); 
  int myint4 = std::stoi (str6);

  if(verify2(myint) != 1 || verify2(myint2) != 1 || verify2(myint3) != 1 || verify2(myint4) != 1){
    std::cout<<"IP inválido (numeros não correspondem aos possiveis valores de alcance),abortando"<<'\n';
    exit(EXIT_SUCCESS);
  }    

  //impressoes respectivas do ip,1o,2o,3o,4o octetos
  /*std::cout <<'\n' <<"Seu IP : " <<str << '\n' <<'\n';
  std::cout<< "Primeiro Octeto : "<<str3<<'\n';
  std::cout<< "Segundo Octeto : "<<str4<<'\n';
  std::cout<< "Terceiro Octeto : "<<str5<<'\n';
  std::cout<< "Quarto Octeto : "<<str6<<'\n'<<'\n';
  */
  if(myint >= 1 && myint <= 127){
    if( numMask < 8){
        std::cout<<"Mascara INVÁLIDA (MÁSCARA NÃO CORRESPONDE AO DEVIDO ALCANCE PARA SUA CLASSE"<<'\n';
        exit(EXIT_SUCCESS);
    }
    std::cout<<"Classe A"<<'\n';
    //std::cout<<"Mascara padrao: 255.0.0.0"<<'\n';
    std::cout<<BLUE<<"Net ID: "<< str3 << ".0.0.0"<<'\n'<<CLEAR;
    std::cout<<RED<<"Host ID: "<<" 0."<< str4 <<"."<<str5<<"."<<str6<<'\n'<<CLEAR;
    if(myint == 10){
      std::cout<<"Esta é uma rede privada !"<<'\n';
    }
  }
  if(myint >=128 && myint <= 191){
    if(numMask < 16){
        std::cout<<"Mascara INVÁLIDA (MÁSCARA NÃO CORRESPONDE AO DEVIDO ALCANCE PARA SUA CLASSE"<<'\n';
        exit(EXIT_SUCCESS);
    }
      std::cout<<"Classe B"<<'\n';
      //std::cout<<"Mascara padrao: 255.255.0.0"<<'\n';
      std::cout<<BLUE<<"Net ID: "<< str3 << "." << str4 <<".0.0"<<'\n'<<CLEAR;
      std::cout<<RED<<"Host ID: "<<" 0.0."<<str5<<"."<<str6<<'\n'<<CLEAR;
      if(myint == 172 && myint2 >= 16 && myint2 <= 31){
        std::cout<<"Esta é uma rede privada !"<<'\n';
      }
  }
  if(myint >=192 && myint <= 223){
    if(numMask < 24){
        std::cout<<"Mascara INVÁLIDA (MÁSCARA NÃO CORRESPONDE AO DEVIDO ALCANCE PARA SUA CLASSE"<<'\n';
        exit(EXIT_SUCCESS);
    }
      std::cout<<"Classe C"<<'\n';
      //std::cout<<"Mascara padrao: 255.255.255.0"<<'\n';
      std::cout<<BLUE<<"Net ID: "<< str3 << "."<<str4 << "." << str5 <<".0"<<'\n'<<CLEAR;
      std::cout<<RED<<"Host ID: "<<" 0.0.0."<<str6<<'\n'<<CLEAR;
      if(myint == 192 && myint2 == 168){
        std::cout<<"Está é uma rede privada !"<<'\n';
      }
  }
  if(myint >= 224 && myint <= 239){
      std::cout<<"Classe D"<<'\n';
  }
  if(myint >= 240 && myint <= 255){
      std::cout<<"Classe E"<<'\n';
  }
  if(myint > 255 || myint < 0){
    std::cout<<"Erro"<<'\n';
  }

  return 0;
}
