enum class DomenError {
    OK=0,
    YEAR_IS_TOO_SMALL=1,
    YEAR_IS_TOO_BIG=2,
    MONTH_IS_TOO_SMALL=3,
    MONTH_IS_TOO_BIG=4,
    DAY_IS_TOO_SMALL=5,
    DAY_IS_TOO_BIG=6,
    HOUR_IS_TOO_SMALL=7,
    HOUR_IS_TOO_BIG=8,
    MINUTE_IS_TOO_SMALL=9,
    MINUTE_IS_TOO_BIG=10,
    SECOND_IS_TOO_SMALL=11,
    SECOND_IS_TOO_BIG=12
};

DomenError CheckDateTimeValidity(const DateTime& dt) {
    int error = 0;
    if (dt.year < 1) {
        error = 1;
    }
    else if (dt.year > 9999) {
        error = 2;
    }

    else if (dt.month < 1) {
        error = 3;
    }
    else if (dt.month > 12) {
        error = 4;
    }
    else {
        const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
        const array month_lengths = { 31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    }
    if (!error) {
        if (dt.day < 1) {
            error = 5;
        }
        else if (dt.day > month_lengths[dt.month - 1]) {
            error = 6;
        }

        else if (dt.hour < 0) {
            error = 7;
        }
        else if (dt.hour > 23) {
            error = 8;
        }

        else if (dt.minute < 0) {
            error = 9;
        }
        else if (dt.minute > 59) {
            error = 10;
        }

        else if (dt.second < 0) {
            error = 11;
        }
        else if (dt.second > 59) {
            error = 12;
        }
    }
    return static_cast<DomenError>(error);
}