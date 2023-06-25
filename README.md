# warehouse-managament-system
This is the project that I make for my project as a First Year university student. <br>
My purpose to do this project is to sharpen my c++ knowledge.<br>
You also need to **download connector file** so that you can connect your c++ with mysql. For this project I used **connector 8.0** <br>
There are 3 file in this repo:<br>
 - db_cppmysql.sql  (This file print all my data from the table)<br>
 - source code UI.cpp  (This file is a basic terminal UI for the system, frontend and backend)<br>
 - SQL table code.sql (table creation code)<br>
 
## Project Description 
 a basic warehouse management system that build using c++ and mysql language.<br>
 This system has several functionality (module):
  ##### 1-Register Staff module
  This module is for the admin register the staff. For register, admin need to insert the detail 
including their staff id ,username, staff ic number, phone number, address. The 
password of the new staff will automatically assign as 123. After staff themselves need 
to change the password.

  ##### 2-Login module
  This module is where admin and staff use their userID and password to log in to the
system. Only authorized user is able to access the system information and data while
unauthorized access will be rejected.
  ##### 3-Update account module
  This module is for the staff and manager can change their own username and password 
details.

  ##### 4-Register stocks module
  This module is for the users to register new stocks into the database. Users need to insert 
information like stocks id, stocks name, stocks category, stocks quantity, stocks location and 
stocks price
  ##### 5-View Stocks module
  This module is for viewing the stocks in the database. Users need to insert the stocks id 
when they want to make searching
  ##### 6-Search module
 This module is for the users to search stocks and view the full detail of stocks. This 
search module is more specific compare to view stocks. Users can search stocks using 
stock id, stock name,price, supplier or registerar name
  ##### 7-Checkout stocks module
  For this module, users can checkout the stocks from the database. Users can choose 
wether they want to checkout all stocks quantity in one go or just a few quantity stocks. 
To checkout the stocks, they need to insert stocks id.
  ##### 8-update stock module
  This module is for the users to update stocks information. Users can update stocks 
information like stock name, stock quantity and supplier name. Before updating, users 
need to insert the stocks id .
  ##### 9-Calculation module
  Calculation module is to calculate the total and statistic of product category in the 
warehouse

