#!/bin/bash

search_dir="sat-benchmarks/petite"
output_file="petite_result.txt"
time_limit="120"

rm $output_file

echo "Filename" "Satisfiable" "runetime in seconds" >> $output_file

for entry in "$search_dir"/*
do
  begin=$(date +%s.%N)
  OUTPUT=$(./solver.exe "$entry" --time "$time_limit" | tail -1) 
  end=$(date +%s.%N)

  runtime=$(echo "$end - $begin" | bc )

echo "$entry" "$OUTPUT" "$runtime" >> $output_file
  
done


