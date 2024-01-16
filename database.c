#include <stdio.h>
#include <sqlite3.h>
#include <ncurses.h>



int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}


int main() {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // Abrir o banco de dados (será criado se não existir)
    rc = sqlite3_open("game_database.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Não foi possível abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Criar a tabela 'players' se não existir
    char *createTableSQL = "CREATE TABLE IF NOT EXISTS players (id INTEGER PRIMARY KEY, name TEXT, max INTEGER);";
    rc = sqlite3_exec(db, createTableSQL, callback, 0, &errMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro na criação da tabela: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    // Inserir dados de exemplo na tabela (substitua com dados reais do jogo)
    char *insertDataSQL = "INSERT INTO players (name, max) VALUES ('Jogador1', 1000);";
    rc = sqlite3_exec(db, insertDataSQL, callback, 0, &errMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro na inserção de dados: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    // Consultar e exibir todos os jogadores e seus maiores scores
    char *selectAllSQL = "SELECT * FROM players;";
    rc = sqlite3_exec(db, selectAllSQL, callback, 0, &errMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro na consulta: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    // Fechar o banco de dados
    sqlite3_close(db);

    return 0;
}

