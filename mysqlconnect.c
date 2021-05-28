#pragma warning(disable:4996)
#include <mysql.h>
#include <string.h>
#include <stdio.h>


#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_NAME "test"
#define CHOP(x) x[strlen(x) - 1] = ' '

char g_cPassward[] = { 0 };

void dbconn(void)
{
    MYSQL* connection = NULL, conn;
    MYSQL_RES* sql_result;
    MYSQL_ROW   sql_row;
    int       query_stat;

    char name[12];
    char tel[12];
    char query[255];

    mysql_init(&conn);

    connection = mysql_real_connect(&conn, DB_HOST,
        DB_USER, DB_PASS,
        DB_NAME, 3306,
        (char*)NULL, 0);

    if (connection == NULL)
    {
        fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
        return 1;
    }

    /*
    query_stat = mysql_query(connection, "select * from address");
    if (query_stat != 0)
    {
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        return 1;
    }
    sql_result = mysql_store_result(connection);
    */

    query_stat = mysql_query(connection, "select * from address where name='hi'");
    if (query_stat != 0)
    {
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        return 1;
    }

    sql_result = mysql_store_result(connection);


    printf("%+11s %-10s", "name", "\ttel \n\n");
    while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
    {

        g_cPassward[1] = sql_row[1];

        printf("%s", g_cPassward);
        printf("%s", sql_row[1]);

        //       printf("%+11s %-10s", sql_row[0], sql_row[1]);
        printf("\n");
    }

    mysql_free_result(sql_result);

    //add
    printf("Nameadd :");
    fgets(name, 12, stdin);
    CHOP(name);


    printf("teladd :");
    fgets(tel, 12, stdin);
    CHOP(tel);

    sprintf(query, "insert into address values "
        "('%s', '%s')",
        name, tel);

    query_stat = mysql_query(connection, query);
    //

    //delete
    printf("Namedel :");
    fgets(name, 12, stdin);
    CHOP(name);

    sprintf(query, "delete from address where name="
        "('%s')",
        name);

    query_stat = mysql_query(connection, query);
    //

    if (query_stat != 0)
    {
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        return 1;
    }

    mysql_close(connection);
}

int main(void) {
    dbconn();

    return 0;
}