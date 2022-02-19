read X
if [[ $X == -* ]]; then
  tmp="${X::-1}"
  if [[ $tmp == "-" ]]; then
    answer="-1"
  else
    if [[ $((X % 10)) == 0 ]]; then
      answer=$tmp
    else
      answer=$((tmp - 1))
    fi
  fi
else
  answer="${X::-1}"
fi

if [[ $answer == "" ]]; then
  echo "0"
else
  echo $answer
fi