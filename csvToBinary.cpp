#include <iostream>
#include <fstream>
using namespace std;

class athlete{
    friend void pegaDados(string &line);
    private:
        int id;
        char name[60];
        char city[30];
        char sport[30];
        char event[60];
        char noc[3];
    public:
        void clear(athlete& atleta);
        void imprimeBinario(const athlete atleta);
};

void athlete::clear(athlete& atleta){
    id = 0;
    for(int i = 0; i < 60; i++){
		if(i < 30){
			atleta.city[i] = '\0';
			atleta.sport[i]= '\0';
		}
		if(i < 3){
			atleta.noc[i] = '\0';
		}
		atleta.name[i] = '\0';
		atleta.event[i] = '\0';
    }
}
void athlete::imprimeBinario(const athlete atleta){
    ofstream arqBin("arquivoBin.dat", ios::binary | ios :: app);
    arqBin.write(reinterpret_cast<const char*>(&atleta), sizeof(athlete));
    arqBin.close();
}
string pegaColuna(string &line, unsigned &i){
    string campo;
    if(i == 0){
        while(line[i] != ','){
            campo = campo + line[i];
            i++;
        }
    }else if(line[i] == ',' and line[i+1] != '"'){
        i++;
        unsigned tam = line.length();
        while(line[i] != ',' and i < tam){
            campo = campo + line[i];
            i++;
        }
    }else{
        i++;
        campo = campo + '"';
        i++;
        while(!(line[i] == '"' and line[i+1] == ',')){
            campo = campo + line[i];
            i++;
        }
        i++;
        campo = campo + '"';
    }
    return campo;
}

void pegaDados(string &line){
    athlete atleta;
    atleta.clear(atleta);
    unsigned i = 0;
    string campo;

    campo = pegaColuna(line, i);
    atleta.id = stoi(campo);
    campo.clear();
 
    campo = pegaColuna(line, i);
    for(unsigned j = 0; j < campo.length(); j++){
        atleta.name[j] = campo[j];
    }
    campo.clear();

    campo = pegaColuna(line, i);
    for(unsigned j = 0; j < campo.length(); j++){
        atleta.city[j] = campo[j];
    }
    campo.clear();

    campo = pegaColuna(line, i);
    for(unsigned j = 0; j < campo.length(); j++){
        atleta.sport[j] = campo[j];
    }
    campo.clear();

    campo = pegaColuna(line, i);
    for(unsigned j = 0; j < campo.length(); j++){
        atleta.event[j] = campo[j];
    }
    campo.clear();

    campo = pegaColuna(line, i);
    for(unsigned j = 0; j < campo.length(); j++){
        atleta.noc[j] = campo[j];
    }
    campo.clear();
    atleta.imprimeBinario(atleta);
}
int main(){
    string nomeArqEntrada;
    nomeArqEntrada = "data_athlete_event.csv";
    ifstream  arquivoCSV(nomeArqEntrada);

	if(arquivoCSV){
        cout << "Conversao do banco de dados Data Athlete Event para arquivo binario foi iniciada." << endl
             << "Por favor aguarde. Voce recebera uma mensagem quando o processo acabar." << endl;
        string line;
        getline(arquivoCSV, line, '\n');
        while(getline(arquivoCSV, line, '\n')){
            pegaDados(line);
		}
        cout << "A conversao foi realizada com sucesso. Agora voce pode utilizar o sistema de manipulacao de arquivo binario." << endl;
    }else{
        cout << "ERRO. O arquivo nao pode ser aberto." << endl;
    }
    arquivoCSV.close();
    return 0;
}
