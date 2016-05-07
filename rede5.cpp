#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <locale>
#include <sstream>
#include <math.h>

#define RED "\e[31m"
#define BLUE "\e[34m"
#define GREEN "\e[92m"
#define CLEAR "\033[0m"

using namespace std;

int global2;//quantidade de blocos completos?
int myint; //valor do primeiro octeto em decimal
int myint2; //valor do segundo octeto em decimal
int myint3; //valor do terceiro octeto em decimal
int myint4; //valor do quarto octeto em decimal

int digits(int i){
   int x=0;
   while(i>9){
      i = i/10;
      x++;
   }
   return x+1;
}

int binary_decimal(int n)//transforma binário em decimal

{
    int decimal=0, i=0, rem;
    while (n!=0)
    {
        rem = n%10;
        n/=10;
        decimal += rem*pow(2,i);
        ++i;
    }
    return decimal;
}

bool verify(int num ){ //verifica se um número é dos possiveis valores para um dos octetos da máscara
  if(num==0 || num == 128 || num == 192 || num == 224 || num == 240 || num == 248 || num == 252 || num == 254 || num == 255){
    return true;
  }
  return false;
}
bool verify2(int num){ //verifica se o numero está no alcance da máscara
  if(num < 0 || num > 255){
    return false;
  }
  return true;
}
int verify3(int num){//função para transformar valores da mascara em forma de classe para o valor em bits no bloco
  if(num == 0){
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
/***
@param num valor do determinado octeto do ip
@param amount numero da mascara em bloco
***/
int calc2(int num,int amount){//calcula endereço de broadcast
  char vet[8];
  //int broad = 32 - amount;
  for(int i=0;i<amount%8;i++){
    vet[i] = '0';
  }
  for(int i=0;i<8-amount%8;i++){
    vet[i+amount%8]='1';
  }
    int result = std::stoi(vet);
    result = binary_decimal(result);
    result = result | num;

 return result;
}


/***
@param num valor do determinado octeto do ip
@param amount numero da mascara em bloco
***/
int calc(int num,int amount){ //funcao que calcula o endereço de rede
    int i; //iterador do vetor
    char vet[8]; //string a ser criada do respectivos valores a serem atribuidos pela quantidade de bits da máscara do ultimo octeto
    for( i=0;i<amount%8;i++){
      vet[i]='1';
    }//setando os primeiros bits em '1's
    for( i=0;i<8-amount%8;i++){
      vet[i+amount%8]='0';
    }//setandos os ultimos bits em '0's

    int result = std::stoi( vet ); //transformando a string em inteiro

    result = binary_decimal(result); //transformando o número binário em decimal

    result = result & num;//AND lógico entre o valor do octeto e o número respectivo à máscara
    
    return result;//binary_decimal(result);
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
  std::string mask ;//("255.255.255.0");
  int check=0;

  std::cout<<"Insira seu IP: ";
  std::getline(std::cin,str);
  if(str=="127.0.0.0"){
    std::cout<<"Está é uma rede reservada para loopback!"<<endl;
    exit(EXIT_SUCCESS);
  }
  //std::cout<<"Insira sua mascara: ";
  //std::getline(std::cin,mask);


  int numMask;
  numMask = checkMask(mask);
  //numMask = std::stoi( mask );
  //std::string node = checkMask(numMask);
  //std::cout <<'\n' <<"Sua Mascara eh: "<< node <<'\n';

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
  myint = std::stoi( str3 );
  myint2 = std::stoi (str4);
  myint3 = std::stoi( str5 );
  myint4 = std::stoi (str6);


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

  std::cout<<GREEN;
  if(myint >= 1 && myint <= 127){
      if( numMask < 8){
        std::cout<<"Mascara INVÁLIDA (MÁSCARA NÃO CORRESPONDE AO DEVIDO ALCANCE PARA SUA CLASSE"<<'\n';
        exit(EXIT_SUCCESS);
      }
      std::cout<<"Classe A"<<'\n';
      if(myint == 10){
        std::cout<<"Esta é uma rede privada !"<<'\n';
      }
      if(numMask<16){
        std::cout<<BLUE<<"Endereço de Rede: " << str3 << "." << calc(myint2,numMask)<<".0.0"<<'\n'<<CLEAR;
        std::cout<<RED<<"Endereço de Broadcast: "<< str3 << "." << calc2(myint2,numMask) << ".255.255"<<'\n'<<CLEAR;
      }
      if(numMask<24 && numMask >= 16){
        std::cout<<BLUE<<"Endereço de Rede: " << str3 << "." << str4 <<"." <<calc(myint3,numMask)<< "." <<"0"<<'\n'<<CLEAR;
        std::cout<<RED<<"Endereço de Broadcast: "<< str3 << "." << str4 << "." << calc2(myint3,numMask) <<".255"<<'\n'<<CLEAR;
      } 
      if(numMask>=24){
        std::cout<<BLUE<<"Endereço de Rede: " << str3 << "." << str4 <<"." << str5 << "." <<calc(myint4,numMask)<<'\n'<<CLEAR;
        std::cout<<RED<<"Endereço de Broadcast: "<< str3 << "." << str4 << "." << str5 <<"."<<calc2(myint4,numMask)<<'\n'<<CLEAR;
      }  
    //std::cout<<"Endereço de Rede: " << str3 <<"." <<calc(myint2,numMask)<< ".0.0"<<'\n';
    //std::cout<<"Endereço de Broadcast: "<< str3 << "." << calc2(myint2,numMask) << ".255.255"<<'\n';  
  }
  if(myint >=128 && myint <= 191){
      
      if(numMask < 16){
        std::cout<<"Mascara INVÁLIDA (MÁSCARA NÃO CORRESPONDE AO DEVIDO ALCANCE PARA SUA CLASSE"<<'\n';
        exit(EXIT_SUCCESS);
      }
      std::cout<<"Classe B"<<'\n';
      if(myint == 172 && myint2 >= 16 && myint2 <= 31){
        std::cout<<"Esta é uma rede privada !"<<'\n';
      }
      if(numMask<24){
        std::cout<<BLUE<<"Endereço de Rede: " << str3 << "." << str4 <<"." <<calc(myint3,numMask)<< "." <<"0"<<'\n'<<CLEAR;
        std::cout<<RED<<"Endereço de Broadcast: "<< str3 << "." << str4 << "." << calc2(myint3,numMask) <<".255"<<'\n'<<CLEAR;
      } 
      if(numMask>=24){
        std::cout<<BLUE<<"Endereço de Rede: " << str3 << "." << str4 <<"." << str5 << "." <<calc(myint4,numMask)<<'\n'<<CLEAR;
        std::cout<<RED<<"Endereço de Broadcast: "<< str3 << "." << str4 << "." << str5 <<"."<<calc2(myint4,numMask)<<'\n'<<CLEAR;
      }     
  }
  if(myint >=192 && myint <= 223){
    if(numMask < 24){
        std::cout<<"Mascara INVÁLIDA (MÁSCARA NÃO CORRESPONDE AO DEVIDO ALCANCE PARA SUA CLASSE"<<'\n';
          exit(EXIT_SUCCESS);
    }
      std::cout<<"Classe C"<<'\n';
      std::cout<<BLUE<<"Endereço de Rede: " << str3 << "." << str4 <<"."<< str5 << "." <<calc(myint4,numMask)<<'\n'<<CLEAR;
      std::cout<<RED<<"Endereço de Broadcast: "<< str3 << "." << str4 << "." << str5 << "." <<calc2(myint4,numMask)<<'\n'<<CLEAR;
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
  std::cout<<GREEN;
  std::cout<<"Quantidade de Hosts por subrede: "<<pow(2,32-numMask)-2<<endl;
  std::cout<<CLEAR;

  return 0;
}
