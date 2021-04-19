var result = null
var number2 = null
var whichInput = 1
var operator = null
setDisplay(0)

/**
 * Resets the state of the calculator and the display
 */
function resetCalc() {
   result = null
   number2 = null
   whichInput = 1
   setDisplay(0)
}

/**
 * Sets the inner text of the div with id="output"
 * @param {String} str the string to set the inner text to
 */
function setDisplay(str) {
   if (str > 999999999) {
      str = 999999999
   }
   document.getElementById("output").innerHTML = str;
}

/**
 * Returns the current result of the calculator
 * Hint: you can use a global variable for the result
 */
function getResult() {
   return parseInt(result)
}

/**
 * Update the calculator state with the next number and sets the display
 * @param {Number} num the number that was pressed
 */
function pressNum(num) {
   if (result != null && whichInput == 1) {
      result = (10*result) + num
      setDisplay(result) 
   }

   if (result == null && whichInput == 1) {
      result = num
      setDisplay(result)
   }

   if (number2 != null && whichInput == 2) {
      number2 = (10*number2) + num
      setDisplay(number2) 
   }

   if (number2 == null && whichInput == 2) {
      number2 = num
      setDisplay(number2) 
   }
}

/**
 * Operation is pressed, move the current result value to a temporary buffer and
 * set the current result to zero.
 * @param {String} op the operation pressed, either: +,-,*,/
 */
function pressOp(op) {
   whichInput = 2
   setDisplay(0) 
   operator = op
}

/**
 * Should compute the current operation with the buffer value and current
 * result value based on the current operation. If there is no current
 * operation, do nothing.
 */
function pressEquals() {
   if (result != null && number2 != null && operator != null)
      if (operator == '+') {
         result = result + number2
         number2 = null
         setDisplay(Math.floor(result))
      }

      if (operator == '-') {
         result = result - number2
         number2 = null
         setDisplay(Math.floor(result))
      }

      if (operator == '/') {
         if (number2 == 0) {
            setDisplay("ERROR")           
         } else {
            result = result / number2
            number2 = null
            setDisplay(Math.floor(result))
         }
      }

      if (operator == '*') {
         result = result * number2
         number2 = null
         setDisplay(Math.floor(result))
      }

}