For this final report, I have inserted the topic and summary about this project


CREATE TABLE stocks(
    STOCKS_ID varchar(10),
    STOCKS_NAME varchar(50),
    STOCKS_CATEGORY varchar(100),
    STOCKS_QUANTITY varchar(1000),
    STOCKS_LOCATION varchar(5),
    STOCKS_PRICE varchar(10),
    Supplier_Name varchar(100),
    RegisterarID varchar(100)
);

CREATE TABLE in_out_stocks(
    STOCKS_ID varchar(10),
    STOCKS_NAME varchar(50),
    STOCKS_CATEGORY varchar(100),
    STOCKS_QUANTITY varchar(1000),
    STOCKS_LOCATION varchar(5),
    STOCKS_INDATE varchar(100), 
    STOCKS_OUTDATE varchar(100),
    MODIFIED_BY varchar(100)
);

CREATE TABLE users(
    userID varchar(10),
    username varchar(100),
    userPassword varchar(50),
    userType varchar(2),
);

CREATE TABLE staff(
    STAFF_ID varchar(10),
    STAFF_NAME varchar(100),
    STAFF_IC varchar(12),
    STAFF_PHONENUMBER varchar(10),
    STAFF_ADDRESS varchar(200)
);
