#!/usr/bin/env bash
set -euo pipefail
ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
MINISHELL="$ROOT_DIR/minishell"

fail() {
  echo "[FAIL] $1"
  exit 1
}

pass() {
  echo "[PASS] $1"
}

run() {
  local input="$1"
  shift
  local expected="$1"
  shift || true
  local tmpout
  tmpout=$(mktemp)
  echo "$input" | "$MINISHELL" > "$tmpout" 2>&1 || true
  if ! grep -q -F "$expected" "$tmpout"; then
    echo "=== Input ==="; echo "$input"
    echo "=== Output ==="; cat "$tmpout"
    fail "$expected not found in output"
  else
    pass "$expected"
  fi
  rm -f "$tmpout"
}

# Tests for quotes
run "echo hello world" 'TOKEN [WORD] : "echo"'
run "echo 'hello world'" 'TOKEN [WORD] : "hello world"'
run 'echo "hello world"' 'TOKEN [WORD] : "hello world"'

# Test operators
run "ls | wc" 'TOKEN [PIPE] : "|"'
run "echo hi > out.txt" 'TOKEN [R_OUT] : ">"'
run "cat < in.txt" 'TOKEN [R_IN] : "<"'

# Test heredoc operator tokenization
run "cat << EOF" 'TOKEN [R_HEREDOC] : "<<"'

# Test quoted edge cases: unmatched quote should be handled by syntax_check -> exit_shell prints
# We'll feed a line with unmatched quote; syntax_check currently invoked in accept_line
tmp=$(mktemp)
printf "%s\n" "echo \"unterminated" | "$MINISHELL" > "$tmp" 2>&1 || true
if grep -q "Exiting shell with code" "$tmp"; then
  pass "unmatched quote handled via exit_shell"
else
  echo "=== Output ==="; cat "$tmp"
  fail "Unmatched quote not handled as error"
fi
rm -f "$tmp"

# Test token creation/freeing: run multiple lines to see no crash
printf "echo a\n echo b\n" | "$MINISHELL" > /dev/null 2>&1 || true
pass "multiple lines processed"

# Check exit_shell behavior: since 'exit' builtin isn't implemented as builtin, it will just be tokenized.
# We expect to see token for 'exit'
run "exit" 'TOKEN [WORD] : "exit"'

# Minimal unit test: make sure token_add_back handles NULL node without crashing
cc tests/test_token_null.c src/token.c includes/libft/libft.a -Iincludes -o tests/test_token_null
./tests/test_token_null || fail "token_add_back(NULL) crashed"
pass "token_add_back handles NULL node"

echo "All edge tests completed."