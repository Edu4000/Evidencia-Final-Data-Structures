#include <iostream>

using namespace std;

class Registro{
	private:
		string mes, hora, ip, errorLog;
		int dia;
	
	public:
		// Def Constructor / O(1)
		Registro(){
		}

		// Constructor / O(1)
		Registro(string mes, int dia, string hora, string ip, string errorLog){
			this->mes = mes;
			this->dia = dia;
			this->hora = hora;
			this->ip = ip;
			this->errorLog = errorLog;
		}

		// Returns port number / O(n) & average O(1)
		string get_port(){
			string res = this->ip.substr(ip.find(":")+1, ip.length());
			return res;
		}

		// Returns port number / O(n) & average O(1)
		string get_ip(){
			string res = this->ip.substr(0, ip.find(":"));
			return res;
		}

		// Get month / O(1)
		string get_mes(){
			return this->mes;
		}

		// Get week number / O(n) & average O(1)
		int get_dia(){
			return this->dia;
		}
};