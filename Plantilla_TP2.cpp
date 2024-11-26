#include <iostream>
// Uso vectores
#include <vector>
// Uso archivos
#include <fstream>
// Uso tolower
#include <cctype>
using namespace std;

const float valordolar = 1000;

// Estructura para representar un movimiento
struct Movimiento
{
    string tipo; // retiro, plazo fijo etc
    string actividad; //descrip
};

// Estructura para representar un plazo fijo
struct PlazoFijo
{
    int dias;
    float inversion;
    float ganancia;
};

// Estructura para representar una cuenta bancaria
struct Cuenta
{
    string nombre;
    string contrasenia;
    float saldo;
    float saldousd;
    string separacion;
    vector <PlazoFijo> plazos_fijos;
    vector <Movimiento> movimientos;
};

void menu_inicial(){
    cout << endl;
    cout << "Bienvenido/a al banco //" << endl;
    cout << "1 - Iniciar Sesión." <<endl;
    cout << "2 - Registrarse." <<endl;
    cout << "3 - Salir del sistema. " << endl;
    cout << endl;
    cout << "Elegir una opcion del menú: " <<endl;
}

// Función para mostrar el menú principal
void menu_principal(Cuenta usuario)
{
    cout << endl;
    cout << "Bienvenido/a al sistema bancario, " << usuario.nombre << endl;
    cout << "Saldo en cuenta: $ " << usuario.saldo << endl;
    cout << "Dólares: USD$ " << usuario.saldousd << endl;
    cout << "Plazos fijos armados: " << usuario.plazos_fijos.size() << endl;
    cout << endl;
    cout << "1 - Ingresar efectivo." << endl;
    cout << "2 - Retirar efectivo." << endl;
    cout << "3 - Comprar y/o vender dólares." << endl;
    cout << "4 - Retirar dólares." << endl;
    cout << "5 - Armar plazo fijo." << endl;
    cout << "6 - Cancelar plazo fijo." << endl;
    cout << "7 - Pedir préstamo." << endl;
    cout << "8 - Ver movimientos." << endl;
    cout << "9 - Actualizar datos." << endl;
    cout << "10 - Salir del sistema." << endl;
    cout << endl;
    cout << "Elegir una opcion del menú: " << endl;
}

// Función para mostrar el menú de movimientos
void menu_movimientos(Cuenta usuario){
    cout << endl;
    cout << "Usted tiene: " << usuario.movimientos.size() << " movimientos en total" << endl;
    cout << "1 - Seleccionar un movimiento" <<endl;
    cout << "Menu - Volver al menu inicial" <<endl;
    cout << endl;
    cout << "Elegir una opcion: " <<endl;
}

// Funcion para mostrar el menu de prestamos
void menu_prestamo(bool saldo1, bool saldo2, bool saldo3){
    cout << endl;
    cout << "Elija una opcion de prestamo" << endl;
    cout << endl;
    if (saldo1) {
        cout << "1. Opcion para saldo mayor a 20,000" << endl;
    }
    if (saldo2) {
        cout << "2. Opcion para saldo mayor a 50,000" << endl;
    }
    if (saldo3) {
        cout << "3. Opcion para saldo mayor a 100,000" << endl;
    }
    // Si no le llega el saldo para ninguna opcion se resuelve fuera de esta funcion
}

// // Menu Inicial Funcion Login
void login(bool &logsuccess, int &indicetxt, int &indicestruct) {
    // Variables para almacenar el nombre y la contraseña ingresados por el usuario
    string nombre, contrasenia;

    // Vector guardar extract
    vector <string> frase;

    // Variable para controlar el ciclo
    bool intentos = true;

    while (intentos) {
        cout << "Ingrese su nombre: ";
        cin >> nombre;
        cout << endl;
        cout << "Ingrese su contraseña: ";
        cin >> contrasenia;
        cout << endl;

        // Abro el archivo en modo lectura
        ifstream archivo("../Cuentas.txt");

        if (archivo.is_open()) {
            string extract;
            bool usuarioEncontrado = false;

            while (getline(archivo, extract)) {
                frase.push_back(extract);
            }

            archivo.close();

            // Buscar el nombre de usuario y validar la contraseña
            for (size_t i = 0; i < frase.size(); i++) {
                if (frase[i] == nombre) { // Usuario encontrado
                    usuarioEncontrado = true;
                    if (i + 1 < frase.size() && frase[i + 1] == contrasenia) {
                        cout << "Sesión iniciada correctamente" << endl;
                        
                        // Índice del nombre en el vector
                        indicetxt = i; 
                        // Índice estructurado
                        indicestruct = (i / 5);

                        logsuccess = true;
                        intentos = false;
                        break;
                    } else {
                        cout << "Contraseña incorrecta" << endl;
                        logsuccess = false;
                        break;
                    }
                }
            }

            if (!usuarioEncontrado) {
                cout << "Usuario inexistente" << endl;
                logsuccess = false;
            }
        } else {
            cout << "Archivo Cuentas.txt inexistente" << endl;
            logsuccess = false;
            intentos = false;
        }

        // Si no se logró iniciar sesión, preguntar si se desea intentar de nuevo
        if (!logsuccess) {
            char opcion;
            cout << "¿Desea intentar nuevamente? (s/n): " << endl;
            cin >> opcion;
            if (tolower(opcion) != 's') {
                intentos = false;
            }
        }
    }
}

// Menu Inicial Funcion Register
void registro(){
    // Variables para extraer del txt
    string extract;

    // Variables a insertar en txt
    string nombre, contrasenia;

    // Variable while
    bool intentos = true;

    // Utilizo un while por si el nombre de usuario ya se encuentra en uso,
    // para que no lo devuelva al menu inicial
    while(intentos){
        // Abro archivo en modo lectura para buscar las variables
        ifstream archivo;
        archivo.open("../Cuentas.txt", ios::in);

        // Variables para extraer del txt
        bool nombredispo = true;

        cout << "Ingrese su nombre: " <<endl;
        cin >> nombre;
        cout << "Ingrese su contraseña: " <<endl;
        cin >> contrasenia;

        // Busco si el nombre ya se encuentra en uso
        if(archivo.is_open()){
            while(getline(archivo, extract) && nombredispo){
                cout<<extract<<endl;
                if(extract == nombre){
                    nombredispo = false;
                    break;
                }
            }
            archivo.close();
            // El nombre se encuentra disponible
            if(nombredispo){
                // Abro el archivo en modo escritura para ingresar los datos del nuevo usuario
                ofstream archivo;
                archivo.open("../Cuentas.txt", ios::app);

                // Ingreso los datos del nuevo usuario con un ! para separar entre linea y linea
                if(archivo.is_open()){
                    archivo << nombre<< endl;
                    archivo << contrasenia<< endl;
                    archivo << 0 <<endl;
                    archivo << 0 <<endl;
                    archivo << "----------" <<endl;
                    cout << "Registro exitoso, inicie sesion para continuar." << endl;
                    archivo.close();
                    intentos=false;
                }
            }
            else {
                cout << "Nombre de usuario ya utilizado" << endl;
                archivo.close();
                char opcion;
                cout << "¿Desea intentar nuevamente? (s/n): " << endl;
                cin >> opcion;
                if (tolower(opcion) != 's') {
                    intentos = false;
                }
            }
        }
        else{
            cout << "Archivo Cuentas.txt inexistente" << endl;
            intentos=false;
        }
    }
}

// Funcion para extraer los datos del txt de cuentas
void extraercuentastxt(vector <Cuenta> &usuario){
    // Creo las variables necesarias
    string extract;
    // Abro txt de las cuentas
    ifstream archivo;
    archivo.open("../Cuentas.txt", ios::in);
    // Extraigo los valores y los mando al vector usuario
    while(getline(archivo,extract)){
        Cuenta cuentatemp;
        cuentatemp.nombre = extract;
        getline(archivo,extract);
        cuentatemp.contrasenia = extract;
        getline(archivo,extract);
        cuentatemp.saldo = stof(extract); // stof
        getline(archivo,extract);
        cuentatemp.saldousd = stof(extract); // stof
        getline(archivo,extract);
        cuentatemp.separacion = extract;
        usuario.push_back(cuentatemp);
    }
}

// Función para extraer los datos del archivo de movimientos
void extraermovtxt(Cuenta &usuario) {
    string extract;
    Movimiento aux;
    vector<string> temp;

    ifstream archivo_movimientos("../Movimientos.txt", ios::in);
    if (archivo_movimientos.is_open()) {
        // Leer todas las líneas del archivo
        while (getline(archivo_movimientos, extract)) {
            temp.push_back(extract);
        }
        archivo_movimientos.close();

        // Procesar los datos extraídos
        for (size_t i = 0; i < temp.size(); ++i) {
            if (temp[i] == usuario.nombre) {
                if (i > 0 && i + 1 < temp.size()) { // Validar índices
                    aux.tipo = temp[i - 1];
                    aux.actividad = temp[i + 1];
                    usuario.movimientos.push_back(aux);
                }
            }
        }
    } else {
        cout << "Archivo Movimientos.txt inexistente" << endl;
    }
}

// Función para extraer los datos del archivo de plazos fijos
void extraerpftxt(Cuenta &usuario) {
    string extract;
    PlazoFijo aux;
    vector<string> temp;

    ifstream archivo_pf("../PlazoFijo.txt", ios::in);
    if (archivo_pf.is_open()) {
        // Leer todas las líneas del archivo
        while (getline(archivo_pf, extract)) {
            temp.push_back(extract);
        }
        archivo_pf.close();

        // Procesar los datos extraídos
        for (size_t i = 0; i < temp.size(); ++i) {
            if (temp[i] == usuario.nombre) {
                if (i + 3 < temp.size()) { // Validar índices
                    aux.dias = stoi(temp[i + 1]);
                    aux.inversion = stof(temp[i + 2]);
                    aux.ganancia = stof(temp[i + 3]);
                    usuario.plazos_fijos.push_back(aux);
                }
            }
        }
    } else {
        cout << "Archivo PlazoFijo.txt inexistente" << endl;
    }
}

// Funcion para cargar los movimientos
void cargarmov(string tipo, string nombre, string descrip, string cantidad, string separacion){
    // Abro el archivo movimiento para cargar esta operacion
    ofstream archivo_movimientos;
    archivo_movimientos.open("../Movimientos.txt", ios::app);
    if (archivo_movimientos.is_open()) {
        archivo_movimientos << tipo << endl;
        archivo_movimientos << nombre << endl;
        archivo_movimientos << descrip << cantidad << endl;
        archivo_movimientos << separacion << endl;
        archivo_movimientos.close();
    } 
    else {
        cout << "Archivo Movimientos.txt inexistente" << endl;
    }
}

// Funcion para cargar los plazos fijo
void cargarpf(string nombre, int dias, float inversion, float resultado, string separacion){
    // Abro el archivo plazofijo para cargar esta operacion
    ofstream archivo_pf;
    archivo_pf.open("../PlazoFijo.txt", ios::app);
    if (archivo_pf.is_open()) {
        archivo_pf << nombre << endl;
        archivo_pf << dias << endl;
        archivo_pf << inversion << endl;
        archivo_pf << resultado << endl;
        archivo_pf << separacion << endl;
        archivo_pf.close();
    } 
    else {
        cout << "Archivo PlazoFijo.txt inexistente" << endl;
    }
}

// Funcion para ingresar plata
void ingresar_efectivo(Cuenta &usuario) {
    // Variables para los archivos
    float ingreso;
    
    cout << "Cuanta plata va a querer ingresar? " <<endl;
    cin>>ingreso;

    //El valor de indicetxt es el del nombre, +2 es igual a su saldo en pesos
    usuario.saldo += ingreso; 
    cout << "Ingreso exitoso" << endl;

    cargarmov("Ingreso", usuario.nombre, "Se Ingreso: ", to_string(ingreso), usuario.separacion);
}

// Funcion para calcular la cantidad de billetes en pesos del retiro
void billetes(int retiro, int denominacion[4], int (&billetesusados)[4], int moneda){
    int i = 0;
    if(moneda = 1){
        // Pesos
        while (retiro >= 100 && i < 4) {
            if (retiro >= denominacion[i]) {
                // Sumo al array la cantidad de billetes que se usaron de esa denominacion
                billetesusados[i] = retiro / denominacion[i];
                // Resto la cantidad de billetes que se usaron de esa denominacion
                retiro -= billetesusados[i] * denominacion[i]; 
            }
            i++;
        }
    }
    if(moneda = 2){
        // Dolares
        while (retiro >= 10 && i < 4) {
            if (retiro >= denominacion[i]) {
                // Sumo al array la cantidad de billetes que se usaron de esa denominacion
                billetesusados[i] = retiro / denominacion[i];
                // Resto la cantidad de billetes que se usaron de esa denominacion
                retiro -= billetesusados[i] * denominacion[i]; 
            }
            i++;
        }
    }
}

// Funcion para retirar pesos
void retirar_efectivo(Cuenta &usuario) {
    // Variable retiro es un int debido a que un numero con , no es multiplo de 100
    int retiro;

    // Variables para el while
    bool intentos = true;

    // Array billetes
    int billetespesos[4] = {1000, 500, 200, 100};
    int billetespesosusados[4] = {0, 0, 0, 0};

    while(intentos){
        cout << "Ingrese un monto multiplo de 100 para retirar" << endl;
        cin>>retiro;
        if(retiro<=usuario.saldo && retiro %100 == 0){
            usuario.saldo -= retiro;
            billetes(retiro, billetespesos, billetespesosusados, 1);
            cout << "Retiro exitoso Se te otorgaron: " << endl;
            cout << billetespesosusados[0] << " billetes de 1000" << endl;
            cout << billetespesosusados[1] << " billetes de 500" << endl;
            cout << billetespesosusados[2] << " billetes de 200" << endl;
            cout << billetespesosusados[3] << " billetes de 100" << endl;
            intentos =  false;
        }
        else{
            cout << "Saldo insuficiente o monto no divisible por 100" << endl;
            char opcion;
            cout << "¿Desea intentar nuevamente? (s/n): " << endl;
            cin >> opcion;
            if (tolower(opcion) != 's') {
                intentos = false;
            }
        }
    }
    
    cargarmov("RetiroPesos", usuario.nombre, "Se retiro: ", to_string(retiro), usuario.separacion);
}

// Funcion para la compra y venta de dolares
void manejar_dolares(Cuenta &usuario) {
    // Variables basicas
    char select, select2, select3;
    int compra, compra2 = (usuario.saldo / valordolar);
    int venta, venta2 = (usuario.saldousd);

    // Variable while
    bool intentos = true;

    while(intentos){
        cout << "¿Desea comprar o vender dolares? (c/v)" << endl;
        cin >> select;
        switch (tolower(select))
        {
        case 'c':
            cout << "¿Cuantos dolares quiere comprar?  " << endl;
            cin >> compra;
            if(compra < usuario.saldo){
                cout << "Va a costar " << (compra *valordolar) << " pesos" <<endl;
                cout << "Saldo suficiente, desea continuar con la compra de " << compra << " dolares? (s/n)" << endl;
                cin >> select2;
                if(tolower(select2) == 's'){
                    cout << "Compra exitosa" <<endl;
                    usuario.saldo -= (compra*valordolar);
                    usuario.saldousd += compra;
                    cargarmov("CompraUsd", usuario.nombre, "Se compro: ", to_string(compra), usuario.separacion);
                }
                else{
                    cout << "Compra cancelada" <<endl;
                }
            }
            else{
                cout << "Saldo insuficiente para esa cantidad, desea continuar la compra pero de " << compra2 << " dolares? (s/n)" << endl;
                cout << "Va a costar " << (compra2 * valordolar) << " pesos" <<endl;
                cin >> select3;
                if(tolower(select3) == 's'){
                    cout << "Compra exitosa" <<endl;
                    usuario.saldo -= (compra2 *valordolar);
                    usuario.saldousd += compra2 ;
                    cargarmov("CompraUsd", usuario.nombre, "Se compro: ", to_string(compra2), usuario.separacion);
                }
                else{
                    cout << "Compra cancelada" <<endl;
                }
            }
            break;
        
        case 'v':
            if(usuario.saldousd < 10){
                cout << "No se cumplen con los requisitos minimos de venta " << endl;
            }
            else{
                cout << "¿Cuando desea vender? " << endl;
                cin >> venta;
                if(venta <= usuario.saldousd){
                    cout << "Dolares suficientes, venta exitosa" << endl;
                    usuario.saldousd -= venta;
                    usuario.saldo += (venta * valordolar);
                    cargarmov("VentaUsd", usuario.nombre, "Se vendio: ", to_string(venta), usuario.separacion);
                }
                else{
                    cout << "Saldo insuficiente para esa cantidad, desea continuar la venta pero de " << venta2 << " dolares? (s/n)" << endl;
                    cin >> select3;
                    if(tolower(select3) == 's'){
                        cout << "Compra exitosa" <<endl;
                        usuario.saldousd -= venta2;
                        usuario.saldo += (venta2 * valordolar);
                        cargarmov("VentaUsd", usuario.nombre, "Se vendio: ", to_string(venta2), usuario.separacion);
                    }
                    else{
                        cout << "Compra cancelada" <<endl;
                    }
                }
            }
            break;

            default:
            cout << "Opcion invalida" <<endl;
            break;
        }
        cout << "¿Desea continuar? (s/n)" << endl;
        char opcion;
        cin >> opcion;
        if (tolower(opcion) != 's') {
            intentos = false;
        }
    }
}

// Funcion para retirar dolares
void retirar_dolares(Cuenta &usuario) {
    // Variable retiro es un int debido a que un numero con , no es multiplo de 10
    int retiro;

    // Variables para el while
    bool intentos = true;

    // Variables de los billetes
    int billetesdolares[4] = {100, 50, 20, 10};
    int billetesdolaresusados[4] = {0, 0, 0, 0};

    while(intentos){
        cout << "Ingrese un monto multiplo de 10 para retirar" << endl;
        cin>>retiro;
        if(retiro<=usuario.saldousd && retiro %10 == 0){
            usuario.saldousd -= retiro;
            billetes(retiro, billetesdolares, billetesdolaresusados, 2);
            cout << "Retiro exitoso Se te otorgaron: " << endl;
            cout << billetesdolaresusados[0] << " billetes de 100" << endl;
            cout << billetesdolaresusados[1] << " billetes de 50" << endl;
            cout << billetesdolaresusados[2] << " billetes de 20" << endl;
            cout << billetesdolaresusados[3] << " billetes de 10" << endl;
            intentos =  false;
        }
        else{
            cout << "Saldo insuficiente o monto no divisible por 10" << endl;
            char opcion;
            cout << "¿Desea intentar nuevamente? (s/n): " << endl;
            cin >> opcion;
            if (tolower(opcion) != 's') {
                intentos = false;
            }
        }
    }
    
    cargarmov("RetiroUsd", usuario.nombre, "Se retiro: ", to_string(retiro), usuario.separacion);
}

// Funcion para armar plazos fijo
void armar_plazo_fijo(Cuenta &usuario) {
    // Variables plazo fijo
    float inversion;
    int dias;
    float ganancia;

    // Variables while
    bool intentos = true;

    while(intentos){
        cout << "Ingrese la inversion para el plazo fijo: " << endl;
        cin >> inversion;
        cout << "Ingrese la cantidad de dias del plazo fijo: (minimo 30d)" <<endl;
        cin >> dias;
        if(dias >= 30 && inversion < usuario.saldo){
            intentos = false;
            usuario.saldo -= inversion;
        }
        else{
            cout << "Cantidad insuficiente de dias o saldo insuficiente" << endl;
        }
    }

    // Informacion para usuario
    cout << "Duracion del plazo fijo: " << dias << " dias" << endl;
    cout << "Inversion: " << inversion << endl;
    ganancia = (inversion * dias * 70) / 36500;
    cout << "Interes generado: " << ganancia << endl;
    cout << "Plata que recibe el usuario al terminar el plazo fijo: " << ganancia+inversion << endl;

    cargarpf(usuario.nombre, dias, inversion, ganancia, usuario.separacion);
    cargarmov("Creacion plazo fijo", usuario.nombre, "Se invirtio: " + to_string(inversion) + " y se genero de interes: " + to_string(ganancia), "", usuario.separacion);   
}

// Funcion para cancelar un plazo fijo y actualizar la struct 
void cancelar_plazo_fijo(Cuenta &usuario) {
    // Variables cancelar plazo fijo
    int id = 0;
    vector <PlazoFijo> temp;

    for(int i = 0; i < usuario.plazos_fijos.size(); i++){
        cout << "Plazo fijo ID: " << i + 1 << endl;
        cout << "Días: " << usuario.plazos_fijos[i].dias << endl;
        cout << "Ganancia: " << usuario.plazos_fijos[i].ganancia << endl;
        cout << "Inversión: " << usuario.plazos_fijos[i].inversion << endl;
        cout << usuario.separacion << endl;
        id++;
    }
    cout << "Que plazo fijo desea cancelar? " << endl;
    cin >> id;
    id -= 1;
    
    usuario.saldo += usuario.plazos_fijos[id].inversion;

    for(int i = 0; i < usuario.plazos_fijos.size(); i++){
        if(i != id){
            temp.push_back(usuario.plazos_fijos[i]);
        }
    }
    usuario.plazos_fijos.clear();
    for(int i = 0; i < temp.size(); i++){
        usuario.plazos_fijos.push_back(temp[i]);
    }

    cargarmov("Cancelacion Plazo Fijo", usuario.nombre, "Se devolvieron: " + to_string(usuario.plazos_fijos[id].inversion) + " pesos", "", usuario.separacion);
}

// Funcion para actualizar el txt despues de cancelar un plazo fijo
void cancelar_plazo_fijo_txt(Cuenta &usuario, bool &primero2){
    // Abrir el archivo PlazoFijo.txt
    ofstream archivo_pf("../PlazoFijo.txt", primero2 ? ios::app : ios::out);
    if (!archivo_pf.is_open()) {
        cout << "Archivo PlazoFijo.txt inexistente" << endl;
        return;
    }

    // Escribir plazos fijos del usuario en PlazoFijo.txt
    for (int i = 0; i < usuario.plazos_fijos.size(); i++) {
        archivo_pf << usuario.nombre << endl;
        archivo_pf << usuario.plazos_fijos[i].dias << endl;
        archivo_pf << usuario.plazos_fijos[i].inversion << endl;
        archivo_pf << usuario.plazos_fijos[i].ganancia << endl;
        archivo_pf << usuario.separacion << endl;
    }

    // Establecer que ya no es el primer usuario
    primero2 = true;
    archivo_pf.close();
}

// Funcion para pedir prestamos
void pedir_prestamo(Cuenta &usuario) {
    // Variables
    int opcion;

    // Variables saldo
    bool saldo1 = usuario.saldo > 20000;
    bool saldo2 = usuario.saldo > 50000; 
    bool saldo3 = usuario.saldo > 100000;
    if(!saldo1 && !saldo2 && !saldo3){
        cout << "No tienes saldo suficiente para ninguna opcion." << endl;
    }
    else{
        cout << endl;
        menu_prestamo(saldo1, saldo2, saldo3);
        cin >> opcion;
        switch (opcion){
            case 1:
            cout << "Prestamo de: " << (usuario.saldo * 0.05) << endl;
            cargarmov("Prestamo otorgado", usuario.nombre, "Se pidio un prestamo basico de: ", to_string(usuario.saldo * 0.05), usuario.separacion);
            usuario.saldo += usuario.saldo * 0.05;
            cout << "Prestamo basico otorgado" << endl;
            break;
        case 2:
            cout << "Prestamo de: " << (usuario.saldo * 0.10) << endl;
            cargarmov("Prestamo otorgado", usuario.nombre, "Se pidio un prestamo medio de: ", to_string(usuario.saldo * 0.10), usuario.separacion);
            usuario.saldo += usuario.saldo * 0.10;
            cout << "Prestamo medio otorgado" << endl;
            break;
        case 3:
            cout << "Prestamo de: " << (usuario.saldo * 0.15) << endl;
            cargarmov("Prestamo otorgado", usuario.nombre, "Se pidio un prestamo premium de: ", to_string(usuario.saldo * 0.15), usuario.separacion);
            usuario.saldo += usuario.saldo * 0.15;
            cout << "Prestamo premium otorgado" << endl;
            break;
        default:
            break;
        }
    }
}

// Funcion para ver un movimiento en detalle
void ver_movimientos(Cuenta usuario) {
    // Variables
    int mov;

    cout << "Que movimiento desea ver: " << endl;
    cin>>mov;
    // Resto uno al movimiento porque el usuario no sabe que arranca en 0 y termina en 9 en caso de tener 10 movimentos
    mov -= 1;
    if(mov >= 0 && mov < usuario.movimientos.size()){
        cout << endl;
        cout << usuario.movimientos[mov].actividad << endl;
        cout << usuario.nombre << endl;
        cout << usuario.movimientos[mov].tipo << endl;
        cout << usuario.separacion << endl;
        cout << endl;
    }
    else{
        cout << "Movimiento invalido" << endl;
    }
}

// Funcion para cambiar el usuario o la contraseña de la cuenta
void actualizar_datos(Cuenta &usuario) {
    // Variables respuesta
    char r;
    string newuser;
    string newpassword;
    string newpassword2;

    // Variables while
    bool intentos = true;
    bool intentos2 = true;

    // Vector con todos los usuarios
    vector <Cuenta> check;

    extraercuentastxt(check);

    cout << "Desea actualizar el usuario o la contraseña? (u/c) " << endl;
    cin >> r;
    switch (r)
    {
    case 'u':
        while(intentos){
            cout << "Ingrese su nuevo nombre de usuario: " <<endl;
            cin >> newuser;
            for(int i = 0; i < check.size(); i++){
                if(newuser == check[i].nombre){
                    intentos2 = true;
                }
            }
            if(newuser == usuario.nombre){
                cout << "No se puede cambiar el nombre de usuario por el mismo" << endl;
                intentos2 = false;
            }
            else if(intentos2){
                cout << "Nombre de usuario ya utilizado" << endl;
                intentos2 = false;
            }
            else{
                usuario.nombre = newuser;
                intentos = false;
            }
        }
        cout << "Nombre de usuario actualizado a : " << usuario.nombre << endl;
        break;
        
    case 'c':
        while (intentos2){
            cout << "Ingrese su nueva contraseña: " << endl;
            cin >> newpassword;
            cout << "Ingrese devuelta su nueva contraseña: " << endl;
            cin >> newpassword2;
            if(newpassword == newpassword2 && newpassword != usuario.contrasenia){
                intentos2 = false;
            }
            else if(newpassword == newpassword2 && newpassword == usuario.contrasenia){
                cout << "No se puede cambiar la contraseña por la misma" << endl;
            }
            else{
                cout << "No coinciden las contraseñas" << endl;
            }
        }
        usuario.contrasenia = newpassword;
        cout << "Contraseña actualizada a: " << usuario.contrasenia << endl;
        break;
    default:
        cout << "Opción no válida." << endl;
        break;
    }
}

// Función para actualizar los datos de los archivos
void salir_sistema(Cuenta usuario, bool &primero) {
    // Abrir el archivo Cuentas.txt
    ofstream archivo("../Cuentas.txt", primero ? ios::app : ios::out);
    if (!archivo.is_open()) {
        cout << "Archivo Cuentas.txt inexistente" << endl;
        return;
    }

    // Escribir datos del usuario en Cuentas.txt
    archivo << usuario.nombre << endl;
    archivo << usuario.contrasenia << endl;
    archivo << usuario.saldo << endl;
    archivo << usuario.saldousd << endl;
    archivo << usuario.separacion << endl;
    archivo.close();

    // Vector movimientos no se encuentra porque eso no se modifica al ser considerado log

    // Vector plazo fijo no se encuentra porque es manejado por el armado y cancelacion de
    // estos mismos

    // Establecer que ya no es el primer usuario
    primero = true;
}


int main()
{
    // Variables
    int opcion1 = 0, opcion2 = 0, opcion3 = 0;
    string opcion3str;
    int indicetxt = 0, indicestruct = 0;
    bool logsuccess=false, primero = false, primero2 = false;
    vector <Cuenta> usuario;

    while(opcion1 != 3 && !logsuccess){
        menu_inicial();
        cin >> opcion1;

        switch (opcion1)
        {
        case 1:
            login(logsuccess, indicetxt, indicestruct);
            break;
        case 2:
            registro();
            break;
        case 3:
            cout << "Gracias por utilizar nuestro sistema, vuelva pronto." << endl;
            break;
        default:
            cout << "Opción no válida. Intente nuevamente." << endl;
            break;
        }
    }
    
    if(logsuccess){
        extraercuentastxt(usuario);
        for(int i = 0; i < usuario.size(); i++){
            extraermovtxt(usuario[i]);
        }
    }

    while (opcion2 != 10 && logsuccess)
    {   
        usuario[indicestruct].plazos_fijos.clear();
        for(int i = 0; i < usuario.size(); i++){
            extraerpftxt(usuario[i]);
        }
        menu_principal(usuario[indicestruct]);
        cin >> opcion2;

        switch (opcion2)
        {
        case 1:
            ingresar_efectivo(usuario[indicestruct]);
            break;
        case 2:
            retirar_efectivo(usuario[indicestruct]);
            break;
        case 3:
            manejar_dolares(usuario[indicestruct]);
            break;
        case 4:
            retirar_dolares(usuario[indicestruct]);
            break;
        case 5:
            armar_plazo_fijo(usuario[indicestruct]);
            break;
        case 6:
            cancelar_plazo_fijo(usuario[indicestruct]);
            for(int i = 0; i < usuario.size(); i++){
                cancelar_plazo_fijo_txt(usuario[i], primero2);
            }
            cout << "Plazo fijo cancelado con exito " << endl;
            break;
        case 7:
            pedir_prestamo(usuario[indicestruct]);
            break;
        case 8:
            while(opcion3 != 2){
                // Limpio el vector movimientos porque sino se acumulan con el siguinte for
                for(int i = 0; i < usuario.size(); i++){
                usuario[i].movimientos.clear();
                }
                // Extraigo todos los movimientos del txt porque si se hizo un movimiento con el sistema abierto
                // no se guarda en la struct, sino que en el txt y al no estar en la struct, no lo va a detectar
                // por lo que no se va a poder ver
                for(int i = 0; i < usuario.size(); i++){
                extraermovtxt(usuario[i]);
                }
                menu_movimientos(usuario[indicestruct]);
                cin >> opcion3str;
                for(int i = 0; i < opcion3str.size(); i++){
                    opcion3str[i] = tolower(opcion3str[i]);
                }
                if(opcion3str == "menu"){
                    opcion3 = 2;
                }
                else{
                    opcion3 = stoi(opcion3str);
                }
                switch (opcion3)
                {
                case 1:
                    ver_movimientos(usuario[indicestruct]);
                    break;
                case 2:
                    cout << "Volviendo al menu principal" << endl;
                    break;
                default:
                    cout << "Opción no válida. Intente nuevamente." << endl;
                    break;
                }
            }
            opcion3 = 0;
            break;
        case 9:
            actualizar_datos(usuario[indicestruct]);
            break;
        case 10:
            for(int i = 0; i < usuario.size(); i++){
                salir_sistema(usuario[i], primero);
            }
            cout << "Gracias por utilizar nuestro sistema " << usuario[indicestruct].nombre << ", vuelva pronto." << endl;
            break;
        default:
            cout << "Opción no válida. Intente nuevamente." << endl;
            break;
        }
    }
}