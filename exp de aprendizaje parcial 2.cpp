#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int MAX_ALUMNOS = 100;
const int MAX_GRUPOS = 50;
const int MAX_MAESTROS = 50;

struct Alumno {
    string nombre;
    string matricula;
    float calif[3];
    int grupo;
};

struct Maestro {
    string nombre;
    string materia;
};

struct Grupo {
    string nombre;
    string carrera;
};

int LeerEntero(string mensaje, int minimo, int maximo);
float LeerCalificacion(string mensaje);
float CalcularPromedio(Alumno alumno);
void CapturarAlumnos(Alumno alumnos[], int& cantidadAlumnos,
    Grupo grupos[], int cantidadGrupos);
void CapturarGrupos(Grupo grupos[], int& cantidadGrupos);
void CapturarMaestros(Maestro maestros[], int& cantidadMaestros);
void MostrarReportes(Alumno alumnos[], int cantidadAlumnos,
    Grupo grupos[], int cantidadGrupos);
void MostrarMenu();

int main() {
    Alumno alumnos[MAX_ALUMNOS];
    Grupo grupos[MAX_GRUPOS];
    Maestro maestros[MAX_MAESTROS];

    int cantidadAlumnos = 0;
    int cantidadGrupos = 0;
    int cantidadMaestros = 0;
    int opcion;

    do {
        MostrarMenu();
        opcion = LeerEntero("Seleccione una opcion: ", 1, 5);

        if (opcion == 1) {
            if (cantidadGrupos == 0) {
                cout << "\nPrimero registre los grupos.\n";
            }
            else {
                CapturarAlumnos(alumnos, cantidadAlumnos,
                    grupos, cantidadGrupos);
            }
        }
        else if (opcion == 2) {
            CapturarGrupos(grupos, cantidadGrupos);
        }
        else if (opcion == 3) {
            CapturarMaestros(maestros, cantidadMaestros);
        }
        else if (opcion == 4) {
            MostrarReportes(alumnos, cantidadAlumnos,
                grupos, cantidadGrupos);
        }
        else if (opcion == 5) {
            cout << "\nPrograma finalizado.\n";
        }

    } while (opcion != 5);

    return 0;
}

void MostrarMenu() {
    cout << "\n===== SISTEMA DE ALUMNOS Y CALIFICACIONES =====\n";
    cout << "1. Capturar alumnos\n";
    cout << "2. Capturar grupos y carreras\n";
    cout << "3. Capturar maestros\n";
    cout << "4. Mostrar reportes\n";
    cout << "5. Salir\n";
}

int LeerEntero(string mensaje, int minimo, int maximo) {
    int valor;

    while (true) {
        cout << mensaje;

        if (cin >> valor && valor >= minimo && valor <= maximo) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }

        cout << "Entrada invalida. Intente de nuevo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

float LeerCalificacion(string mensaje) {
    float calificacion;

    while (true) {
        cout << mensaje;

        if (cin >> calificacion &&
            calificacion >= 0 && calificacion <= 10) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return calificacion;
        }

        cout << "Ingrese una calificacion entre 0 y 10.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

float CalcularPromedio(Alumno alumno) {
    float promedio;

    promedio = (alumno.calif[0] + alumno.calif[1]
        + alumno.calif[2]) / 3;

    return promedio;
}

void CapturarGrupos(Grupo grupos[], int& cantidadGrupos) {
    int disponibles = MAX_GRUPOS - cantidadGrupos;

    if (disponibles == 0) {
        cout << "\nYa se alcanzo el limite de grupos.\n";
        return;
    }

    int cantidad = LeerEntero(
        "Cuantos grupos desea registrar? ", 1, disponibles);

    for (int i = 0; i < cantidad; i++) {
        cout << "\nGrupo " << cantidadGrupos + 1 << endl;

        cout << "Ingrese el nombre del grupo: ";
        getline(cin, grupos[cantidadGrupos].nombre);

        cout << "Ingrese la carrera: ";
        getline(cin, grupos[cantidadGrupos].carrera);

        cantidadGrupos++;
    }

    cout << "\nGrupos registrados correctamente.\n";
}

void CapturarMaestros(Maestro maestros[], int& cantidadMaestros) {
    int disponibles = MAX_MAESTROS - cantidadMaestros;

    if (disponibles == 0) {
        cout << "\nYa se alcanzo el limite de maestros.\n";
        return;
    }

    int cantidad = LeerEntero(
        "Cuantos maestros desea registrar? ", 1, disponibles);

    for (int i = 0; i < cantidad; i++) {
        cout << "\nMaestro " << cantidadMaestros + 1 << endl;

        cout << "Ingrese el nombre del maestro: ";
        getline(cin, maestros[cantidadMaestros].nombre);

        cout << "Ingrese la materia: ";
        getline(cin, maestros[cantidadMaestros].materia);

        cantidadMaestros++;
    }

    cout << "\nMaestros registrados correctamente.\n";
}

void CapturarAlumnos(Alumno alumnos[], int& cantidadAlumnos,
    Grupo grupos[], int cantidadGrupos) {
    int disponibles = MAX_ALUMNOS - cantidadAlumnos;

    if (disponibles == 0) {
        cout << "\nYa se alcanzo el limite de alumnos.\n";
        return;
    }

    int cantidad = LeerEntero(
        "Cuantos alumnos desea registrar? ", 1, disponibles);

    cout << "\nGrupos disponibles:\n";

    for (int i = 0; i < cantidadGrupos; i++) {
        cout << i + 1 << ". " << grupos[i].nombre
            << " | Carrera: " << grupos[i].carrera << endl;
    }

    for (int i = 0; i < cantidad; i++) {
        cout << "\nAlumno " << cantidadAlumnos + 1 << endl;

        cout << "Ingrese el nombre: ";
        getline(cin, alumnos[cantidadAlumnos].nombre);

        cout << "Ingrese la matricula: ";
        getline(cin, alumnos[cantidadAlumnos].matricula);

        for (int j = 0; j < 3; j++) {
            alumnos[cantidadAlumnos].calif[j] =
                LeerCalificacion(
                    "Ingrese la calificacion " + to_string(j + 1) + ": ");
        }

        alumnos[cantidadAlumnos].grupo =
            LeerEntero("Seleccione el numero del grupo: ",
                1, cantidadGrupos);

        cantidadAlumnos++;
    }

    cout << "\nAlumnos registrados correctamente.\n";
}

void MostrarReportes(Alumno alumnos[], int cantidadAlumnos,
    Grupo grupos[], int cantidadGrupos) {
    if (cantidadAlumnos == 0) {
        cout << "\nTodavia no hay alumnos registrados.\n";
        return;
    }

    cout << "\n===== PROMEDIOS DE ALUMNOS =====\n";

    for (int i = 0; i < cantidadAlumnos; i++) {
        cout << "Nombre: " << alumnos[i].nombre
            << " | Matricula: " << alumnos[i].matricula
            << " | Promedio: " << CalcularPromedio(alumnos[i])
            << endl;
    }

    cout << "\n===== MEJOR PROMEDIO POR GRUPO =====\n";

    for (int i = 0; i < cantidadGrupos; i++) {
        int mejorAlumno = -1;
        float mejorPromedio = -1;

        for (int j = 0; j < cantidadAlumnos; j++) {
            if (alumnos[j].grupo == i + 1) {
                float promedio = CalcularPromedio(alumnos[j]);

                if (promedio > mejorPromedio) {
                    mejorPromedio = promedio;
                    mejorAlumno = j;
                }
            }
        }

        cout << "\nGrupo: " << grupos[i].nombre << endl;

        if (mejorAlumno == -1) {
            cout << "No hay alumnos en este grupo.\n";
        }
        else {
            cout << "Mejor alumno: "
                << alumnos[mejorAlumno].nombre << endl;
            cout << "Promedio: " << mejorPromedio << endl;
        }
    }

    cout << "\n===== ALUMNOS POR CARRERA =====\n";

    for (int i = 0; i < cantidadGrupos; i++) {
        bool carreraRepetida = false;

        for (int j = 0; j < i; j++) {
            if (grupos[i].carrera == grupos[j].carrera) {
                carreraRepetida = true;
            }
        }

        if (!carreraRepetida) {
            int total = 0;

            for (int j = 0; j < cantidadAlumnos; j++) {
                int indiceGrupo = alumnos[j].grupo - 1;

                if (grupos[indiceGrupo].carrera == grupos[i].carrera) {
                    total++;
                }
            }

            cout << "Carrera: " << grupos[i].carrera
                << " | Cantidad de alumnos: " << total << endl;
        }
    }
}