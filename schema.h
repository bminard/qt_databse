#ifndef _SCHEMA_H_
#define _SCHEMA_H_

#include <vector>

namespace Database {

/*! @brief Class interface to the whole-part heirarchy of the database schema.
 * @note The application should use this class to manage all database migrations.
 *
 * The Schema provides the interface used to initiate a database migration. It
 * can be a table reiviosn or a collection of tables (and their revisions). It
 * fulfills the requirements of the *Composite* component in the Composite
 * design pattern.
 */
class Schema
{
public:
    /*! @brief Virtual destructor for the database schema object.
     */
    virtual ~Schema() = 0;

    /*! @brief Carry out database migration from revision \f$n\f$ to \f$n + 1, n > 0\f$.
     */
    virtual const bool migrate() = 0;

protected:
    /*! @brief Construct the database schema object.
     */
    Schema() noexcept { }
};

/*! @brief Extend the Schema interface to a single table revision.
 *
 * The TableRevision provides the interface used to create a table revision. It
 * contains a single SQL statement which, when executed, changes the table
 * structure. It fulfills the requirements of the *Leaf* component in the
 * Composite design pattern.
 */
class TableRevision
    : public Schema
{
public:
    typedef const char *sql_statement_type;

    /*! @brief Construct the query defining the revised table structure.
     * @param q an SQL statement
     */
    TableRevision(sql_statement_type s): sql_statement(s) {
    }

    /*! @brief Destructor for the table revision object.
     */
    ~TableRevision() { }

    /*! @brief Carry out table migration from revision \f$n\f$ to revision \f$n + 1\f$.
     * @returns true iff the migration succeeds; false otherwise
     */
    virtual const bool migrate();

private:
    sql_statement_type sql_statement;
};

} // name space

#endif // _SCHEMA_H_
