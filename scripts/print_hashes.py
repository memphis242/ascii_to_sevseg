import sys

numbers = [69, 101, 82, 114, 79, 111]

try:
   user_input = int(sys.argv[1])
   for num in numbers:
      print(num % user_input)
except ValueError:
   print("Please enter a valid integer.")