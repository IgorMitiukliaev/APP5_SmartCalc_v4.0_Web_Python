# SmartCalc v4.0

Implementation of SmartCalc v4.0 in Python.

## Contents

1. [Chapter I](#chapter-i) \
   1.1. [Introduction](#introduction)
2. [Chapter II](#chapter-ii) 
3. [Chapter III](#chapter-iii) \
   3.1. [Part 1](#part-1-implementation-of-smartcalc-v40) \
   3.2. [Part 2](#part-2-bonus-loan-сalculator) \
   3.3. [Part 3](#part-3-bonus-deposit-calculator) \
   3.4. [Part 4](#part-4-bonus-configuration-and-logging) \
   3.5. [Part 5](#part-5-bonus-js-graphs)


## Chapter I



## Introduction

In this project you are to implement in Python programming language an extended version of the usual calculator, 
which implements the same functions as the previously developed applications in the SmartCalc v1.0, v2.0, v3.0 projects. 
You will improve your knowledge of the Python programming language, MVC pattern and the basics of Web application development.


## Chapter II

### Incliuding JavaScript to the page

JavaScript can be included into HTML in two ways:
- writing the code inside the HTML,
- including it in as a link to an external file.

The most common way to include JavaScript is as an external file.

##### Tag Script

The `<script>` tag is what is used to include JavaScript. It is similar to the `<link>` tag which is used to connect CSS files.

Here is a very simple piece of JavaScript that uses the `script` tag. This JavaScript is written directly to the HTML page. It will change the title of the paragraph when the button is clicked.

```
<p id="demo">A Paragraph</p>
<button type="button" onclick="myFunction()">Try it</button>

<script>
function myFunction() {
  document.getElementById("demo").innerHTML = "Paragraph changed.";
}
</script>
```

##### Including an external file

To include an external JavaScript file, you can use the `script` tag with the `src` attribute. The value of the src attribute must be the path to the JavaScript file. Then the example above will look like this. 

myScript.js file:
```
function myFunction() {
  document.getElementById("demo").innerHTML = "Paragraph changed.";
}
```

HTML file:
```
<p id="demo">A Paragraph</p>
<button type="button" onclick="myFunction()">Try it</button>

 <script src="myScript.js"></script> 
```

##### Including in Head

Normally you should include external JavaScript files not in the `<body>` of the HTML file but in the `<head>`. Then the same example will look like this:
```
<html>
  <head>
    <script src="myScript.js"></script> 
  </head>
  <body>

    <p id="demo">A Paragraph</p>
    <button type="button" onclick="myFunction()">Try it</button>

  </body>
</html> 
```


## Chapter III

## Part 1. Implementation of SmartCalc v4.0

It is necessary to implement SmartCalc v4.0:

- The program must be developed in Python 3.11
- The program code must be located in the src folder
- It is necessary to follow Google Code Style when writing the code
- It is necessary to develop the Web-application
- The application must be implemented using MVC framework (Django or flask)
- The program must be implemented using the MVC (100% Server-Side Rendering) pattern, and
    - There should be no business logic code in the view code
    - there must be no interface code in the controller and model
    - controllers must be thin
- The model must be completely reused from the SmartCalc v3.0 project
- The application must implement a free-form help section describing the program interface
- The program must store the history of operations, allow to load expressions from the history and clear the entire history
- The history should be saved between application starts
- Both integers and real numbers, written either via a point or in exponential form, can be input to the program
- Calculation should be performed after the complete entry of the calculated expression and pressing the symbol `=`
- Calculation of arbitrary bracketed arithmetic expressions in infix notation
- Calculation of arbitrary bracketed arithmetic expressions in infix notation with substitution of _x_ variable as a number
- Plotting a function defined using an expression in infix notation with the variable _x_ (with coordinate axes, scale marker, and grid with adaptive step)
	- It is not necessary to provide the user with the ability to change the scale
- The range of definition and the range of value of the functions are at least limited to numbers from -1000000 to 1000000
- To plot a function it is necessary to additionally specify the displayed area of definition and area of value
- Checked accuracy of the fractional part is at least 7 decimal places
- The user must be able to enter up to 255 characters
- Bracketed arithmetic expressions in infix notation must support the following arithmetic operations and mathematical functions:
    - **Arithmetic operators**:

      | Operator name | Infix Notation <br />(Classic) | Prefix notation <br /> (Polish notation) |  Postfix notation <br />(Reverse Polish notation) |
      | ------ | ------ | ------ | ------ |
      | Parentheses | (a + b) | (+ a b) | a b + |
      | Addition | a + b | + a b | a b + |
      | Subtraction | a - b | - a b | a b - |
      | Multiplication | a * b | * a b | a b * |
      | Division| a / b | / a b | a b \ |
      | Rasing to the power | a ^ b | ^ a b | a b ^ |
      | Remainder of division | a mod b | mod a b | a b mod |
      | Unary plus | +a | +a | a+ |
      | Unary minus | -a | -a | a- |

      >Please note that the multiplication operator contains a mandatory `*` sign. Processing an expression with the `*` sign omitted is optional and left to the developer's discretion

    - **Functions**:

      | Function description | Function |   
      | ---------------- | ------- |  
      | Calculates cosine | cos(x) |   
      | Calculates sine | sin(x) |  
      | Calculates tangent | tan(x) |  
      | Calculates arc cosine | acos(x) | 
      | Calculates the arcsine | asin(x) | 
      | Calculates arctangent | atan(x) |
      | Calculates square root | sqrt(x) |
      | Calculates natural logarithm | ln(x) | 
      | Calculates decimal logarithm | log(x) |

## Part 2. Bonus. Loan сalculator

Provide a special mode "loan calculator" (you can take websites like banki.ru and calcus.ru as an example):
- Input: total loan amount, term, interest rate, type (annuity, differentiated)
- Output: monthly payment, overpayment for the loan, total repayment

## Part 3. Bonus. Deposit calculator

Provide a special mode "deposit calculator" (you can take websites like banki.ru and calcus.ru as an example):
- Input: deposit amount, deposit term, interest rate, tax rate, periodicity of payments, capitalization of interest, list of additions, list of partial withdrawals
- Output: accrued interest, tax amount, amount on deposit by the end of the term

## Part 4. Bonus. Configuration and logging

Add settings to the app:
- Add reading of settings from configuration file when the program runs
- Include in the configuration file 3 or more parameters to choose from, such as background color, font size, etc.
- Add descriptions of editable parameters to help

Add logging to the application:
- Store operation history in logs
- Save logs in the logs folder, one file per rotation period
- It should be possible to set the period of logs rotation (hour/day/month)
- Files must be named according to the following pattern: `logs_dd-MM-yy-hh-mm-ss` ( the time of file creation )

## Part 5. Bonus. JS-graphs

- Implement the component related to rendering graphs as a JS component with client-side rendering
