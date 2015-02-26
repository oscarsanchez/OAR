/* 
 * File:   main.cpp
 * Author: oscar
 *
 * Created on 22 de febrero de 2015, 06:30 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <iomanip>

using namespace std;

/* Declaracion de Funciones
 */
int printMenu(int);
void defStruct(int);
void addRecord();

struct Field{
	char name[15];
	int integer;
	int size;
};

struct Table{
    vector<Field> fields;
};

struct Record{
    vector<Field> fields;
};

istream& operator>>(istream& in, Field& field){
	in >> field.name >> field.integer >> field.size;
	return in;
}
ostream& operator<<(ostream& out, const Field& field){
	out << field.name << field.integer << field.size;
	return out;
}

int main(int argc, char** argv) {
    int opcion;
    do{
        opcion = printMenu(0);
        if(opcion==1)
        {
            cout << "Ingrese la cantidad de campos que tendra su estructura: ";
            int fields;
            cin >> fields;
            defStruct(fields);
        }
        else if(opcion==2)
        {
            addRecord();
	}
	else if(opcion==4)
        {
            
        }
        else if(opcion==5)
        {
            
	}
	else if(opcion==6)
        {
            
        }
        else if(opcion==7)
        {
            
        }
        else if(opcion==8)
        {
            
        }
        else if(opcion==9)
        {
            cout << "Gracias por confiar en nosotros" << endl;
        }
        else 
		{
			cout << "Opcion seleccionada no existe" << endl;
		}
	}	
	while(opcion != 9);
    
    return 0;
}

int printMenu(int index)
{
    int returnVal;
    if(!index){
        cout << "1) Definir Estructura " << endl;
        cout << "2) Agregar Registro " << endl;
        cout << "3) Listar Registros " << endl;
        cout << "4) Buscar " << endl;
        cout << "5) Borrar " << endl;
        cout << "6) Modificar " << endl;
        cout << "7) Compactar " << endl;
        cout << "8) Activar Indice Lineal " << endl;
        cout << "9) Salir " << endl;
        cout << "Por favor seleccione una opcion:  " ;
    }else{
        cout << "1) Definir Estructura " << endl;
        cout << "2) Agregar Registro " << endl;
        cout << "3) Listar Registros " << endl;
        cout << "4) Buscar " << endl;
        cout << "5) Borrar " << endl;
        cout << "6) Modificar " << endl;
        cout << "7) Compactar " << endl;
        cout << "8) Desactivar Indice Lineal " << endl;
        cout << "9) Salir " << endl;
        cout << "Por favor seleccione una opcion:  " ;
    }
    cin >> returnVal;
    return returnVal;
}

void defStruct(int fields){
    Field lstfields[fields];
    int rrn=0;
    for (int i = 0; i < fields; i++) {
        cout << "Ingrese Nombre del campo N°"<<(i+1)<<": ";
        cin >> lstfields[i].name;
        cout << "Tipo 1 -> [Entero] | 0 -> [Texto]:";
        cin >> lstfields[i].integer;
        if (lstfields[i].integer) {
            lstfields[i].size=4;
        } else {
            cout << "Ingrese Tamaño del texto: ";
            cin >> lstfields[i].size;
        }
        rrn=rrn+lstfields[i].size;
    }
    int availist = -1;
    int records=0;
    ofstream erase;
    erase.open("data.bin", std::ofstream::out | std::ofstream::trunc);
    erase.close();
    ofstream header("data.bin",ios::app | ios::binary); 
    header.write(reinterpret_cast<char*>(&availist),sizeof(int));
    header.write(reinterpret_cast<char*>(&fields),sizeof(int));
    header.write(reinterpret_cast<char*>(&rrn),sizeof(int));
    header.write(reinterpret_cast<char*>(&records),sizeof(int));
    header.close();
    ofstream out("data.bin", ios::app|ios::binary);
    for (int i = 0; i < fields; i++) {
        out.write(reinterpret_cast<char*>(&lstfields[i]),sizeof(Field));
    }
    out.close();

}

void addRecord(){
    ifstream in("data.bin", ios::in|ios::binary);
    int availist;
    int records=0;
    in.read((char*)&availist, sizeof(int));
    int fields;
    in.read((char*)&fields, sizeof(int));
    int rrn;
    in.read((char*)&rrn, sizeof(int));
    char buffer[rrn];
    Field arrFields[fields];
    in.read((char*)&records, sizeof(int));
    for (int i = 0; i < fields; i++) {
        in.read(reinterpret_cast<char*>(&arrFields[i]),sizeof(Field));
    }
    int actualbyte=0;
    for (int i = 0; i < fields; i++) {
        cout << "Ingrese " << arrFields[i].name << ": ";
        char input[rrn*2];
        if (!arrFields[i].integer) {
            char input[rrn*2];
            cin >> input;
            for (int i = 0; i < rrn; i++) {
                buffer[actualbyte+i] = input[i];
                if (input[i] == '\0') break; //if the string is shorter than MAXI
            }
            actualbyte=1+actualbyte+arrFields[i].size;
        } else {
            char input[rrn*2];
            cin >> input;
            for (int i = 0; i < rrn; i++) {
                buffer[actualbyte+i] = input[i];
                if (input[i] == '\0') break; //if the string is shorter than MAXI
            }
            actualbyte=1+actualbyte+arrFields[i].size;
        }

    }
    


}