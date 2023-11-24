#define DECLARE_INT_PARAM(Name) \
    struct Name {               \
        int value;              \
        explicit Name(int v)    \
            : value(v) {        \
        }                       \
        operator int() const {  \
            return value;       \
        }                       \
    } 

#define DECLARE_SV_PARAM(Name)          \
    struct Name {                       \
        string_view value;              \
        explicit Name(string_view v)    \
            : value(v) {                \
        }                               \
        operator string_view() const {  \
            return value;               \
        }                               \
    }

DECLARE_SV_PARAM(DBName);
DECLARE_INT_PARAM(DBConnectionTimeout);
DECLARE_INT_PARAM(MinAge);
DECLARE_INT_PARAM(MaxAge);
DECLARE_SV_PARAM(NameFilter);

struct DBAllowExceptions {
    bool value;
    explicit DBAllowExceptions(bool v):value(v){
    }
};

struct DBLogLevelStruct {
    DBLogLevel value;
    explicit DBAllowExceptions(DBLogLevel v) :value(v) {
    }
};



vector<Person> LoadPersons(DBName db_name, DBConnectionTimeout db_connection_timeout, DBAllowExceptions db_allow_exceptions,
    DBLogLevelStruct db_log_level, MinAge min_age, MaxAge max_age, NameFilter name_filter) {
    DBConnector connector(db_allow_exceptions, db_log_level);
    DBHandler db;
    if (db_name.starts_with("tmp."s)) {
        db = connector.ConnectTmp(db_name, db_connection_timeout);
    }
    else {
        db = connector.Connect(db_name, db_connection_timeout);
    }
    if (!db_allow_exceptions && !db.IsOK()) {
        return {};
    }

    ostringstream query_str;
    query_str << "from Persons "s
        << "select Name, Age "s
        << "where Age between "s << min_age << " and "s << max_age << " "s
        << "and Name like '%"s << db.Quote(name_filter) << "%'"s;
    DBQuery query(query_str.str());

    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({ move(name), age });
    }
    return persons;
}