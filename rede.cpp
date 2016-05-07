#include <iostream>       // std::cout
#include <string>         // std::string

#define BLUE "\e[34m"
#define RED "\e[31m"
#define CLEAR "\033[0m"
#define GREEN "\e[92m"

using namespace std;
int main ()
{
  std::string str; //("192.168.7.2"); //ip do usuario
  std::string str2 ("."); //string a ser procurada
  std::string str3; //primeiro octeto do ip
  std::string str4; // segundo octeto do ip
  std::string str5; //terceiro octeto do ip
  std::string str6; //quarto octeto do ip

  int check = 0;
  std::cout<<"Insira seu IP: ";
  std::getline(std::cin,str);
  if(str=="127.0.0.0"){
    std::cout<<"Está é uma rede reservada para loopback!"<<endl;
    exit(EXIT_SUCCESS);
  }
  // different member versions of find in the same order as above:
  std::size_t found = str.find(str2); //elemento que vai procurar o . nas strings
  if (found!=std::string::npos){
    //std::cout << "first 'dot' found at: " << found << '\n';
    check++;
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
     std::cout<<"IP inválido,abortando"<<'\n';
     return 0;
  }

  //impressoes respectivas do ip,1o,2o,3o,4o octetos
  /*std::cout <<'\n' <<"Seu IP : " <<str << '\n' <<'\n';
  std::cout<< "Primeiro Octeto : "<<str3<<'\n';
  std::cout<< "Segundo Octeto : "<<str4<<'\n';
  std::cout<< "Terceiro Octeto : "<<str5<<'\n';
  std::cout<< "Quarto Octeto : "<<str6<<'\n'<<'\n';
*/
  //transformacoes das strings para inteiros
  int myint = std::stoi( str3 ); 
  int myint2 = std::stoi (str4);

  if(myint >= 1 && myint <= 127){
      std::cout<<"Classe A"<<'\n';
      std::cout<<GREEN<<"Mascara padrao: 255.0.0.0"<<'\n'<<CLEAR;
      std::cout<<BLUE<<"Net ID: "<< str3 << ".0.0.0"<<'\n'<<CLEAR;
      std::cout<<RED<<"Host ID: "<<" 0."<< str4 <<"."<<str5<<"."<<str6<<'\n'<<CLEAR;
      if(myint == 10){
        std::cout<<"Esta é uma rede privada !"<<'\n';
      }
  }
  if(myint >=128 && myint <= 191){
      std::cout<<"Classe B"<<'\n';
      std::cout<<GREEN<<"Mascara padrao: 255.255.0.0"<<'\n'<<CLEAR;
      std::cout<<BLUE<<"Net ID: "<< str3 << "." << str4 <<".0.0"<<'\n'<<CLEAR;
      std::cout<<RED<<"Host ID: "<<" 0.0."<<str5<<"."<<str6<<'\n'<<CLEAR;
      if(myint == 172 && myint2 >= 16 && myint2 <= 31){
        std::cout<<"Esta é uma rede privada !"<<'\n';
      }
  }
  if(myint >=192 && myint <= 223){
      std::cout<<"Classe C"<<'\n';
      std::cout<<GREEN<<"Mascara padrao: 255.255.255.0"<<'\n'<<CLEAR;
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
