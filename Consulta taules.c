//Buscar el Map.id de les partides d'un jugador

//programa en C para consultar los datos de la base de datos
//Incluir esta libreria para poder hacer las llamadas en shiva2.upc.es
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query [100];
	char query2 [100];
	int gameId;
	
	//Creamos una conexion al servidor MYSQL
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "Tanks",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	// consulta SQL para obtener una tabla con todos los datos
	// de la base de datos
	
	strcpy(query, "SELECT DISTINCT Game.id_Map FROM (Player, Game, Participant) WHERE Player.name = '");
	
	printf("Enter the name of the person of whom you want to see the maps in where he/she played:\n");
	scanf("%s", query2);

	strcat(query, query2);
	
	strcpy(query2, "' AND Player.id = Participant.id_P AND Participant.id_G = Game.id");
	strcat(query, query2);
	
	err=mysql_query (conn, query);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//recogemos el resultado de la consulta. El resultado de la
	//consulta se devuelve en una variable del tipo puntero a
	//MYSQL_RES tal y como hemos declarado anteriormente.
	//Se trata de una tabla virtual en memoria que es la copia
	//de la tabla real en disco.
	res = mysql_store_result (conn);
	// El resultado es una estructura matricial en memoria
	// en la que cada fila contiene los datos de una persona.
	// Ahora obtenemos la primera fila que se almacena en una
	// variable de tipo MYSQL_ROW
	row = mysql_fetch_row (res);
	// En una fila hay tantas columnas como datos tiene
	
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		printf ("Map IDs:\n");
		while (row !=NULL) {
			gameId = atoi (row[0]);
			printf ("%d\n", gameId);
			// obtenemos la siguiente fila
			row = mysql_fetch_row (res);
	}
	
	mysql_close (conn);
	exit(0);
}
