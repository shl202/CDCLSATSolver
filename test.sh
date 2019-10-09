#!/bin/bash

search_dir="sat-benchmarks/petite"
output_file="petite_result.txt"

  entry="$1"
  begin=$(date +%s.%N)
  OUTPUT=$(./main.exe "$entry" | tail -1) 
  end=$(date +%s.%N)

  runtime=$(echo "$end - $begin" | bc )

  echo "$entry" "|" "$OUTPUT"  "|" "$runtime" >> $output_file
  


