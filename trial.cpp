#include <iostream>
#include <fstream>	// Leer el archivo
#include <sstream>	// tokenizar el string de cada registro
#include <random>
#include "tablahash.h"
#include "registro.h"

using namespace std;

// O(1)
bool sort_frq_str(const pair<string,int> &a,
			  const pair<string,int> &b)
{
	return (a.second > b.second);
}

// O(1)
bool sort_frq_int(const pair<int,int> &a,
			  const pair<int,int> &b)
{
	return (a.second > b.second);
}

// O(n)
template <typename D>
void add_reg(vector<pair<D,int>>* logs, D data){
	if(logs->size() > 0){
		for(int i = 0; i < logs->size(); i++){
			if(logs->at(i).first == data){
				logs->at(i).second++;
				return;
			}
		}
	}
	logs->push_back(pair<D,int>(data,1));
	return;
}

int main(int nargs, char * args[] ) {

	// Limiting arguments for main / O(1)
	if(nargs == 0){
		cerr << "Error por numero de argumentos: Ningun argumento recibido" << endl;
		exit(1);
	} else if (nargs > 2){
		cerr << "Error por numero de argumentos: Demasiados argumentos recibido" << endl;
		exit(2);
	}

	// Get file name from arguments / O(1)
	string fileName = string(args[1]);
	
	// Create a text string, which is used to output the text file / O(1)
	string mes, hora, ip, errorLog, myText, aux;
	int dia;
	Registro dummy;

	// Data Structures Initialization
	hash<string> hashF;
	vector<pair<string,int>>* ips = new vector<pair<string,int>>();
	vector<pair<string,int>>* ports = new vector<pair<string,int>>();
	vector<pair<int,int>>* weeks = new vector<pair<int,int>>();

	HashTable<string, vector<Registro>*> bitacora(100000);
	
	// HashTable para dias acumulados por mes
	HashTable <string, int> dias_acum (32);
	dias_acum.put("Jan",2);
	dias_acum.put("Feb",33);
	dias_acum.put("Mar",61);
	dias_acum.put("Apr",92);
	dias_acum.put("May",122);
	dias_acum.put("Jun",153);
	dias_acum.put("Jul",183);
	dias_acum.put("Aug",213);
	dias_acum.put("Oct",245);
	dias_acum.put("Sep",275);
	dias_acum.put("Nov",306);
	dias_acum.put("Dec",336);

	// Read from the text file / O(1)
	ifstream MyReadFile(fileName);

	// Use a while loop together with the getline() function to read the file line by line / O(n)
	cout << "\nLEYENDO ARCHIVO" << endl;
	int ctr = 0;
	while (getline (MyReadFile, myText)){
		if(ctr < 1000){
			ctr++;
		}else{
			ctr = 0;
			cout << "#";
		}

		istringstream tokens(myText);
		tokens >> mes;		// O(1)
		tokens >> dia;		// O(1)
		tokens >> hora;		// O(1)
		tokens >> ip;		// O(1)
		errorLog = "";		// O(1)
		// O(1) 
		while(getline (tokens, aux)){
			errorLog = aux;
			errorLog.erase(0,1);
		}

		dummy = Registro(mes, dia, hora, ip, errorLog);	// O(1)

		// Adding Registros
		add_reg(ips, dummy.get_ip());
		add_reg(ports, dummy.get_port());
		// O(1)
		int week = 1 + (dummy.get_dia() + dias_acum.get(dummy.get_mes()))/7;
		add_reg(weeks, week);

	}
	cout << "\nLECTURA DE ARCHIVO FINALIZADA" << endl;

	// Close the file / O(1)
	MyReadFile.close();

	// ################################################################
	// ###              RESPUESTAS EVIDENCIA FINAL                  ###
	// ################################################################

	// ¿Cuáles son las cinco direcciones IP (sin importar el número de puerto) que tuvieron más accesos ilegales?
	cout << "\n--> Direcciones IP con mas accesos ilegales" << endl;
	sort(ips->begin(), ips->end(), sort_frq_str);
	for(int i = 0; i < 5; i++){
		cout << i+1 << ": " << ips->at(i).first << " (" << ips->at(i).second << " accesos ilegales)" << endl;
	}

	// ¿Con qué frecuencia aparecen cada uno de los distintos mensajes de error (razón de la falla)?
	

	// ¿Cuántos números de puertos distintos fueron atacados en total?
	cout << "\n--> Cuantos numeros de puertos distintos fueron atacados en total?" << endl;
	cout << "Numero de Puertos atacados: " << ports->size() << endl;

	// ¿En qué semana se detectaron una mayor cantidad de accesos ilegales? Se puede suponer que: 1) una semana inicia el día lunes y termina el domingo, y 2) las fechas de los archivos de bitácoras corresponden al año 2020.
	cout << "\n--> En que semana se detectaron una mayor cantidad de accesos ilegales?" << endl;
	sort(weeks->begin(), weeks->end(), sort_frq_int);
	cout << "Semana: " << weeks->size() << endl;




	return 0;
}