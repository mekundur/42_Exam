#!/bin/bash

# Path to your binary
BIN=./a.out

# Test cases: input | expected output
tests=(
  "1|1$"
  "2+3|5$"
  "3*4+5|17$"
  "3+4*5|23$"
  "(3+4)*5|35$"
  "(((((2+2)*2+2)*2+2)*2+2)*2+2)*2|188$"
  "1+|Unexpected end of input$"
  "1+2)|Unexpected token ')'$"
  "2*(5+6|Unexpected end of input$"
)

echo "Running tests..."

pass=0
fail=0

for test in "${tests[@]}"; do
  input="${test%%|*}"
  expected="${test##*|}"
  output=$($BIN "$input" | cat -e)

  if [ "$output" = "$expected" ]; then
    echo "✅ '$input' => OK"
    ((pass++))
  else
    echo "❌ '$input' => Expected: '$expected' | Got: '$output'"
    ((fail++))
  fi
done

echo
echo "Total: $((pass+fail)), Passed: $pass, Failed: $fail"
