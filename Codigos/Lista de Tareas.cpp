#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <sstream>
#include <algorithm>
using namespace std;

class Tarea {
protected:
    int id;
    string descripcion;
    string estado;
public:
    Tarea(int id, const string& desc, const string& est = "pendiente")
        : id(id), descripcion(desc), estado(est) {}
    virtual ~Tarea() {}
    int getId() const { return id; }
    string getDescripcion() const { return descripcion; }
    string getEstado() const { return estado; }
    virtual void mostrar() const {
        cout << "ID: " << id << ", Descripción: " << descripcion
             << ", Estado: " << estado << endl;
    }
    virtual void marcarCompletada() { estado = "completada"; }
    virtual string serializar() const {
        return to_string(id) + "|" + descripcion + "|" + estado;
    }
};

class TareaPendiente : public Tarea {
public:
    TareaPendiente(int id, const string& desc)
        : Tarea(id, desc, "pendiente") {}
};

class TareaCompletada : public Tarea {
public:
    TareaCompletada(int id, const string& desc)
        : Tarea(id, desc, "completada") {}
    void mostrar() const override {
        cout << "[✔] ID: " << id << " - " << descripcion << " (" << estado << ")" << endl;
    }
};

class GestorTareas {
private:
    vector<unique_ptr<Tarea>> tareas;
    string archivo;
public:
    GestorTareas(const string& nombreArchivo) : archivo(nombreArchivo) { cargar(); }
    void agregarTarea(int id, const string& desc) {
        tareas.push_back(make_unique<TareaPendiente>(id, desc));
        guardar();
    }
    void mostrarTareas() const {
        if (tareas.empty()) {
            cout << "No hay tareas." << endl;
            return;
        }
        for (const auto& t : tareas) t->mostrar();
    }
    void marcarCompletada(int id) {
        for (auto& t : tareas) {
            if (t->getId() == id) {
                t->marcarCompletada();
                cout << "Tarea " << id << " marcada como completada." << endl;
                guardar();
                return;
            }
        }
        cout << "Tarea no encontrada." << endl;
    }
    void eliminarTarea(int id) {
        auto it = remove_if(tareas.begin(), tareas.end(),
            [id](const unique_ptr<Tarea>& t) { return t->getId() == id; });
        if (it != tareas.end()) {
            tareas.erase(it, tareas.end());
            cout << "Tarea eliminada." << endl;
            guardar();
        } else {
            cout << "Tarea no encontrada." << endl;
        }
    }
    void guardar() const {
        ofstream out(archivo);
        for (const auto& t : tareas) out << t->serializar() << "\n";
    }
    void cargar() {
        ifstream in(archivo);
        if (!in.is_open()) return;
        string linea;
        while (getline(in, linea)) {
            stringstream ss(linea);
            string idStr, desc, est;
            if (getline(ss, idStr, '|') && getline(ss, desc, '|') && getline(ss, est)) {
                int id = stoi(idStr);
                if (est == "pendiente")
                    tareas.push_back(make_unique<TareaPendiente>(id, desc));
                else
                    tareas.push_back(make_unique<TareaCompletada>(id, desc));
            }
        }
    }
};

void menu() {
    cout << "\n--- GESTOR DE TAREAS ---\n";
    cout << "1. Agregar tarea\n";
    cout << "2. Mostrar tareas\n";
    cout << "3. Marcar tarea como completada\n";
    cout << "4. Eliminar tarea\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opción: ";
}

int main() {
    GestorTareas gestor("tareas.txt");
    int opcion, id;
    string descripcion;
    do {
        menu();
        cin >> opcion;
        cin.ignore();
        switch (opcion) {
            case 1:
                cout << "ID de la tarea: ";
                cin >> id;
                cin.ignore();
                cout << "Descripción: ";
                getline(cin, descripcion);
                gestor.agregarTarea(id, descripcion);
                break;
            case 2:
                gestor.mostrarTareas();
                break;
            case 3:
                cout << "ID de la tarea a marcar como completada: ";
                cin >> id;
                gestor.marcarCompletada(id);
                break;
            case 4:
                cout << "ID de la tarea a eliminar: ";
                cin >> id;
                gestor.eliminarTarea(id);
                break;
            case 0:
                cout << "Saliendo del sistema.\n";
                break;
            default:
                cout << "Opción no válida.\n";
                break;
        }
    } while (opcion != 0);
    return 0;
}
