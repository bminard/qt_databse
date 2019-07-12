// Example from Davide Coppola. Article at http://blog.davidecoppola.com/2016/11/howto-embed-database-in-application-with-sqlite-and-qt/.
// See https://github.com/vivaladav/BitsOfBytes/blob/master/howto-embed-database-in-application-with-sqlite-and-qt/QtSqlExample/MainWindow.cpp

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

#include "database.h"

/*! @brief Create an SQLite database.
 * @param path the path to the database
 */
void Database::connect(const QString &path) {
    const QString DRIVER("QSQLITE");
    if(QSqlDatabase::isDriverAvailable(DRIVER)) {
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

        db.setDatabaseName(path);

        if(!db.open()) {
            qWarning() << "connect - ERROR: " << db.lastError().text();
        }
    }
    else {
        qWarning() << "connect - ERROR: no driver " << DRIVER << " available";
    }
}


/*! @brief Initialize the database.
 * @note Call this function only if the database needs to be created from
 *      scratch (i.e., is empty).
 */
void Database::init() {
	QSqlQuery query("CREATE TABLE people (id INTEGER PRIMARY KEY, name TEXT)");

	if(!query.isActive())
		qWarning() << "MainWindow::DatabaseInit - ERROR: " << query.lastError().text();
}
