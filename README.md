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
   3.5. [Part 5](#part-5-bonus-js-charts)


## Chapter I

![APP_5_SmartCalc_V4.0](misc/images/APP_5_SmartCalc_V4.0.jpg)

Thomas found it extremely difficult to remain calm, but nevertheless he tried his best to hold on. He faced Chuck, who was extremely stubborn and tired, but still defended his position to the bitter end. The discussion between them was in full swing:

`-` "OOP in Python? Don't be ridiculous, Thomas!" Chuck smiled sneeringly.

`-` "Imagine that, yes. Maybe not quite built-in, but still," Thomas parried.

`-` "Yeah, well, you have to put in some extra modules to use the interfaces. Not kludge at all," Chuck continued to get indignant. - "And private fields can still be accessed from the outside!"

`-` "At least I don't need to bring up the JVM to quickly check something in the code," Thomas was still trying very hard to remain calm. It was obvious that Python was one of the best programming languages. "And then search all over again what's causing the lack of memory on the computer!"

`-` "At least I wouldn't have to run around the code looking for a random declaration of class fields in the middle of the code," Chuck couldn’t calm down.

`-` "Right. You'll be looking for them in the middle of tons of text. Remind me how you write the output into the console?"

`-` "John, tell him that Python is *syntactically unsuited* to OOP," Chuck glanced hopefully at John, sitting quietly in the corner, apparently enjoying what was happening. Thomas wanted to ask Eve for help in this case, but unfortunately, she was busy at the moment - she was closely monitoring the logs in the terminal.

`-` "I hate to break it to you guys, but we all know Go's got a nose for Java and Python, too. I can even prove it!"

After these words, a nightmare began in the city's most high-tech basement. \
At this moment, you were infiltrating one of the most secure segments of the corporate SIS network in search of hidden accounting data. The access you got from the local SIS system administrator was still enough to wander around the gut of the network without any problems...

## Introduction

In this project you will implement an extended version of the regular calculator in Python programming language, with the same functions as the previously developed applications in the SmartCalc v1.0, v2.0, v3.0 projects.
You will improve your knowledge of the Python programming language, MVC pattern and the basics of Web application development.


## Chapter II

### Including JavaScript to the page

JavaScript can be included into HTML in two ways:

- writing the code inside the HTML,
- including it in as a link to an external file.

The most common way to include JavaScript is as an external file.

#### Tag Script

The `<script>` tag is what we use to include JavaScript. It's a lot like the `<link>` tag you've already been using to include CSS files.

Here's a very basic snippet of JavaScript using the `script` tag. This JavaScript is written directly into an HTML page. It will change the name of the paragraph when the button is pressed.

```html
<p id="demo">A Paragraph</p>
<button type="button" onclick="myFunction()">Try it</button>

<script>
function myFunction() {
  document.getElementById("demo").innerHTML = "Paragraph changed.";
}
</script>
```

##### Including an external file

To include an external JavaScript file, you can use the `script` tag with the `src` attribute. The value for the src attribute should be the path to the JavaScript file. Then the example above will look like this.

myScript.js file:

```javascript
function myFunction() {
  document.getElementById("demo").innerHTML = "Paragraph changed.";
}
```

HTML file:

```html
<p id="demo">A Paragraph</p>
<button type="button" onclick="myFunction()">Try it</button>

 <script src="myScript.js"></script> 
```

##### Including in Head

Normally you should include external JavaScript files not in the `<body>` of the HTML file but in the `<head>`. Then the same example will look like this:

```html
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

You need to implement SmartCalc v4.0:

- The program must be developed in Python 3.11
- The program code must be located in the src folder
- You must stick to Google Code Style when writing code
- You need to develop a Web-application
- The application must be implemented using MVC framework (Django or flask)
- The program must be implemented using the MVC (100% Server-Side Rendering) pattern, and
  - There should be no business logic code in the view code
  - there must be no interface code in the controller and model
  - controllers must be thin
- The model must be completely reused from the SmartCalc v3.0 project
- A help section in a free-form describing the program interface must be implemented in the application
- The program must store the history of operations, allow loading expressions from the history and clear the entire history
- The history should be saved between application starts
- Both integers and real numbers, written either via a point or in exponential form, can be input to the program
- Calculation should be performed after the complete entry of the calculated expression and pressing the symbol `=`
- Calculation of arbitrary bracketed arithmetic expressions in infix notation
- Calculation of arbitrary bracketed arithmetic expressions in infix notation with substitution of *x* variable as a number
- Plotting a function defined using an expression in infix notation with the variable *x* (with coordinate axes, scale marker, and grid with adaptive step)
  - It is not necessary to provide the user with the ability to change the scale
- The range of definition and the range of value of the functions are at least limited to numbers from -1000000 to 1000000
- To plot a function it is necessary to additionally specify the displayed area of definition and area of value
- Checked accuracy of the fractional part is at least 7 decimal places
- The user must be able to enter up to 255 characters
- Bracketed arithmetic expressions in infix notation must support the following arithmetic operations and mathematical functions:
  - **Arithmetic operators**:

      | Operator name | Infix Notation <br />(Classic) | Prefix notation <br /> (Polish notation) | Postfix notation <br />(Reverse Polish notation) |
      | ------ | ------ | ------ | ------ |
      | Parentheses | (a + b) | (+ a b) | a b + |
      | Addition | a + b | + a b | a b + |
      | Subtraction | a - b | - a b | a b - |
      | Multiplication | a * b | * a b | a b * |
      | Division| a / b | / a b | a b \ |
      | Raising to the power | a ^ b | ^ a b | a b ^ |
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

## Part 5. Bonus. JS-charts

- Implement the component related to rendering charts as a JS component with client-side rendering

💡 [Tap here](https://forms.yandex.ru/cloud/64183038d04688004c656bb9/) **to leave your feedback on the project**. Pedago Team really tries to make your educational experience better.
