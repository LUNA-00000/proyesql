#include <iostream>
#include <mysql.h>
#include <vector>
#include <string>

using namespace std;
/*Autor: Dana Hicely Estrada Martinez
*fecha 06/06/2024
*Clase:* conexionMySQL
**Descripcion:**
* Clase que maneja la conexión a la base de datos MySQL
*/
class ConexionMySQL {
private:
    MYSQL* conexion;

public:
    // Constructor
    ConexionMySQL();
    // Destructor
    ~ConexionMySQL();

    // Métodos públicos
    bool abrir_conexion(); // Método para abrir la conexión
    bool cerrar_conexion(); // Método para cerrar la conexión
    bool ejecutar_query(const string& query); // Método para ejecutar una consulta
    MYSQL_RES* ejecutar_select(const string& query); // Método para ejecutar una consulta SELECT
};

// Clase que representa un Boleto de avión
class Boleto {
private:
    // Variables miembro
    string nombre;
    string fechaSalida;
    string fechaLlegada;
    string asiento;
    string numeroVuelo;

public:
    // Constructores
    Boleto() = default;
    Boleto(const string& nombre, const string& fechaSalida, const string& fechaLlegada, const string& asiento, const string& numeroVuelo)
        : nombre(nombre), fechaSalida(fechaSalida), fechaLlegada(fechaLlegada), asiento(asiento), numeroVuelo(numeroVuelo) {}

    // Getters
    string get_nombre() const { return nombre; }
    string get_fecha_salida() const { return fechaSalida; }
    string get_fecha_llegada() const { return fechaLlegada; }
    string get_asiento() const { return asiento; }
    string get_numero_vuelo() const { return numeroVuelo; }

    // Setters
    void set_nombre(const string& nombre) { this->nombre = nombre; }
    void set_fecha_salida(const string& fechaSalida) { this->fechaSalida = fechaSalida; }
    void set_fecha_llegada(const string& fechaLlegada) { this->fechaLlegada = fechaLlegada; }
    void set_asiento(const string& asiento) { this->asiento = asiento; }
    void set_numero_vuelo(const string& numeroVuelo) { this->numeroVuelo = numeroVuelo; }

    // Método para mostrar los detalles del boleto
    void mostrar_detalles() const;
};

// Clase que maneja las operaciones CRUD para los boletos
class ControllerBoletos {
private:

public:
    static ConexionMySQL conexion;

    // Métodos públicos
    static bool crear(Boleto& boleto);
    static bool leer(Boleto& boleto);
    static bool actualizar(Boleto& boleto);
    static bool borrar(Boleto& boleto);
    static void ver_todos(); // Declaración del nuevo método
};

ConexionMySQL ControllerBoletos::conexion;

// Implementación de los métodos de la clase ConexionMySQL
ConexionMySQL::ConexionMySQL() {
    conexion = mysql_init(NULL);
}

ConexionMySQL::~ConexionMySQL() {
    mysql_close(conexion);
}

bool ConexionMySQL::abrir_conexion() {
    if (conexion == NULL) {
        cout << "Error al inicializar la conexion." << endl;
        return false;
    }
    //SQL STRING
    if (!mysql_real_connect(conexion, "localhost", "root", "root", "aerolinea", 3306, NULL, 0)) {
        cout << "Error al conectar a la base de datos: " << mysql_error(conexion) << endl;
        return false;
    }

    cout << "Conexion establecida." << endl;
    return true;
}

bool ConexionMySQL::cerrar_conexion() {
    mysql_close(conexion);
    cout << "Conexión cerrada." << endl;
    return true;
}

bool ConexionMySQL::ejecutar_query(const string& query) {
    if (mysql_query(conexion, query.c_str())) {
        cout << "Error en la consulta: " << mysql_error(conexion) << endl;
        return false;
    }

    cout << "Consulta ejecutada correctamente." << endl;
    return true;
}

MYSQL_RES* ConexionMySQL::ejecutar_select(const string& query) {
    if (mysql_query(conexion, query.c_str())) {
        cout << "Error en la consulta: " << mysql_error(conexion) << endl;
        return nullptr;
    }

    return mysql_store_result(conexion);
}

// Implementación de los métodos CRUD de la clase ControllerBoletos
bool ControllerBoletos::crear(Boleto& boleto) {
    string query = "INSERT INTO boletos (nombre, fecha_salida, fecha_llegada, asiento, numero_vuelo) VALUES ('"
                    + boleto.get_nombre() + "', '" + boleto.get_fecha_salida() + "', '" + boleto.get_fecha_llegada()
                    + "', '" + boleto.get_asiento() + "', '" + boleto.get_numero_vuelo() + "')";
    bool resultado = conexion.ejecutar_query(query);

    if (resultado) {
        query = "SELECT LAST_INSERT_ID()";
        MYSQL_RES* res = conexion.ejecutar_select(query);
        if (res) {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row) {
                // Opcional: usar el ID para alguna operación
            }
            mysql_free_result(res);
        }
    }

    return resultado;
}

bool ControllerBoletos::leer(Boleto& boleto) {
    string query = "SELECT * FROM boletos WHERE nombre = '" + boleto.get_nombre() + "'";
    MYSQL_RES* res = conexion.ejecutar_select(query);

    if (res) {
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            boleto.set_fecha_salida(row[1]);
            boleto.set_fecha_llegada(row[2]);
            boleto.set_asiento(row[3]);
            boleto.set_numero_vuelo(row[4]);
            mysql_free_result(res);
            return true;
        }
    }

    return false;
}

bool ControllerBoletos::actualizar(Boleto& boleto) {
    string query = "UPDATE boletos SET fecha_salida = '" + boleto.get_fecha_salida()
                    + "', fecha_llegada = '" + boleto.get_fecha_llegada()
                    + "', asiento = '" + boleto.get_asiento()
                    + "', numero_vuelo = '" + boleto.get_numero_vuelo()
                    + "' WHERE nombre = '" + boleto.get_nombre() + "'";
    return conexion.ejecutar_query(query);
}

bool ControllerBoletos::borrar(Boleto& boleto) {
    string query = "DELETE FROM boletos WHERE nombre = '" + boleto.get_nombre() + "'";
    return conexion.ejecutar_query(query);
}

// Método para mostrar los detalles del boleto
void Boleto::mostrar_detalles() const {
    cout << "Nombre: " << nombre << endl;
    cout << "Fecha de Salida: " << fechaSalida << endl;
    cout << "Fecha de Llegada: " << fechaLlegada << endl;
    cout << "Asiento: " << asiento << endl;
    cout << "Número de Vuelo: " << numeroVuelo << endl;
}

// Implementación del método para ver todos los boletos en forma de tabla
void ControllerBoletos::ver_todos() {
    string query = "SELECT * FROM boletos";
    MYSQL_RES* res = conexion.ejecutar_select(query);

    if (res) {
        cout << "#\tNombre\t\tFecha de Salida\t\tFecha de Llegada\tAsiento\tNúmero de Vuelo" << endl;
        cout << "----------------------------------------------------------------------------------------------" << endl;
        int i=1;
        while (MYSQL_ROW row = mysql_fetch_row(res)) {
            cout << i++ << "\t" <<  row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t" << row[4] << endl;

        }
        mysql_free_result(res);
    } else {
        cout << "Error al obtener los boletos de la base de datos." << endl;
    }
}
// Función principal para demostrar el uso de las clases y métodos definidos
int main() {
    int opcion;

    // Abrir conexión a la base de datos
    ControllerBoletos::conexion.abrir_conexion();

    do {
        cout << "Menu:" << endl;
        cout << "1. Crear boleto" << endl;
        cout << "2. Leer boleto" << endl;
        cout << "3. Actualizar boleto" << endl;
        cout << "4. Borrar boleto" << endl;
        cout << "5. Ver todos los boletos" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                // Crear un nuevo boleto
                {
                    string nombre_pasajero;
                    string fecha_salida;
                    string fecha_llegada;
                    string asiento;
                    string numero_vuelo;
                    cout << "Ingrese el nombre: ";
                    cin >> ws; // Limpiar el buffer del teclado
                    getline(cin, nombre_pasajero);

                    cout << "Ingrese la fecha de salida (YYYY-MM-DD HH:MM:SS): ";
                    getline(cin,fecha_salida);
                    //cin >> fecha_salida;

                    cout << "Ingrese la fecha de llegada (YYYY-MM-DD HH:MM:SS): ";
                    getline(cin,fecha_llegada);
                    //cin >> fecha_llegada;

                    cout << "Ingrese el asiento: ";
                    cin >> asiento;

                    cout << "Ingrese el número de vuelo: ";
                    cin >> numero_vuelo;

                    Boleto boleto(nombre_pasajero, fecha_salida, fecha_llegada, asiento, numero_vuelo);
                    ControllerBoletos::crear(boleto);
                }
                break;
            case 2:
                // Leer un boleto
                {
                    string nombre_pasajero;
                    cout << "Ingrese el nombre del pasajero: ";
                    cin >> ws; // Limpiar el buffer del teclado
                    getline(cin, nombre_pasajero);
                    Boleto boleto(nombre_pasajero, "", "", "", "");
                    if (ControllerBoletos::leer(boleto)) {
                        boleto.mostrar_detalles();
                    } else {
                        cout << "No se encontró el boleto." << endl;
                    }
                }
                break;
            case 3:
                // Actualizar un boleto
                {
                    string nombre_pasajero;
                    cout << "Ingrese el nombre del pasajero: ";
                    cin >> ws; // Limpiar el buffer del teclado
                    getline(cin, nombre_pasajero);
                    Boleto boleto(nombre_pasajero, "", "", "", "");
                    if (ControllerBoletos::leer(boleto)) {
                        string nueva_fecha_salida, nueva_fecha_llegada, nuevo_asiento, nuevo_numero_vuelo;
                        cout << "Ingrese la nueva fecha de salida (YYYY-MM-DD HH:MM:SS): ";
                        getline(cin,nueva_fecha_salida);
                        //cin >> nueva_fecha_salida;

                        cout << "Ingrese la nueva fecha de llegada (YYYY-MM-DD HH:MM:SS): ";
                        getline(cin,nueva_fecha_llegada);
                        //cin >> nueva_fecha_llegada;

                        cout << "Ingrese el nuevo asiento: ";
                        cin >> nuevo_asiento;

                        cout << "Ingrese el nuevo número de vuelo: ";
                        cin >> nuevo_numero_vuelo;

                        boleto.set_fecha_salida(nueva_fecha_salida);
                        boleto.set_fecha_llegada(nueva_fecha_llegada);
                        boleto.set_asiento(nuevo_asiento);
                        boleto.set_numero_vuelo(nuevo_numero_vuelo);
                        ControllerBoletos::actualizar(boleto);
                    } else {
                        cout << "No se encontró el boleto." << endl;
                    }
                }
                break;
            case 4:
                // Borrar un boleto
                {
                    string nombre_pasajero;
                    cout << "Ingrese el nombre del pasajero: ";
                    cin >> ws; // Limpiar el buffer del teclado
                    getline(cin, nombre_pasajero);
                    Boleto boleto(nombre_pasajero, "", "", "", "");
                    if (ControllerBoletos::borrar(boleto)) {
                        cout << "Boleto eliminado correctamente." << endl;
                    } else {
                        cout << "No se encontro el boleto." << endl;
                    }
                }
                break;
            case 5:
                // Ver todos los boletos
                ControllerBoletos::ver_todos();
                break;
            case 6:
                // Salir del programa
                break;
            default:
                cout << "Opción no válida. Intentelo de nuevo." << endl;
        }
    } while (opcion != 6);

    // Cerrar conexión a la base de datos
    ControllerBoletos::conexion.cerrar_conexion();

    return 0;
}

/*
// Función principal para demostrar el uso de las clases y métodos definidos
int main() {
    cout<<"este esta bien";
    int a;
    cin>>a;
    // Crear un objeto Boleto
    Boleto boleto("Juan Garcia", "2024-05-01 08:00:00", "2024-05-01 12:00:00", "A12", "VUELO123");

    // Abrir conexión a la base de datos
    ControllerBoletos::conexion.abrir_conexion();

    // Crear boleto en la base de datos
    ControllerBoletos::crear(boleto);

    // Leer boleto de la base de datos
    ControllerBoletos::leer(boleto);
    boleto.mostrar_detalles();

    // Actualizar la fecha de salida del boleto
    boleto.set_fecha_salida("2024-05-01 09:00:00");
    ControllerBoletos::actualizar(boleto);

    // Leer y mostrar nuevamente el boleto actualizado
    ControllerBoletos::leer(boleto);
    boleto.mostrar_detalles();
    ControllerBoletos::ver_todos();
    // Borrar boleto de la base de datos
    ControllerBoletos::borrar(boleto);

    // Cerrar conexión a la base de datos
    ControllerBoletos::conexion.cerrar_conexion();

    return 0;
}
*/
