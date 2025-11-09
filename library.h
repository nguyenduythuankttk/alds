#pragma once
#include <string>
#include "employee.h"
#include "person.h"
#include "vector.h"
#include "user.h"
#include "product.h"
#include "warehouse.h"
#include "purchaseorder.h"
#include <sstream>
#include <fstream>
#include <iostream>
void main_menu();
void sign_up(Vector <User>&);
void user_sign_in(User &,Vector <User>&);
void employee_sign_in();