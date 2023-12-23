text = open('input.txt').read()
lines = text.splitlines()
m, n = len(lines), len(lines[0])

# Check special map properties, crucial for hard part.
assert m == n == 131
assert lines[m // 2][n // 2] == 'S'
start = (m // 2, n // 2)

# Only remember the wavefront. This works on my input, but maybe not always?
def solve_easy_better(lines, start, k):
  sizes = [0, 1]
  cur_set, prev_set = set([start]), set()
  for t in range(k):
    prev_set, cur_set = cur_set, set([
      (ii, jj) for i, j in cur_set for ii, jj in [(i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)]
      if lines[ii % m][jj % n] != '#' and (ii, jj) not in prev_set])
    sizes.append(sizes[-2] + len(cur_set))
  return sizes[1:]


step_count = 26501365
# step count is in fact 2023*100*131 + 65.
assert step_count % m == (m - 1) // 2


def delta_sub(lst, d=1):
  return [y - x for x, y in zip(lst[:-d], lst[d:])]


def solve_hard_interpolate(lines, start, step_count):
  sizes = solve_easy_better(lines, start, m * 5)[step_count % m:: m]
  print("sizes:", sizes)
  diff = delta_sub(sizes)
  print("diff:", diff)
  diff_diff = delta_sub(diff)
  print("diff_diff:", diff_diff)
  assert len(set(diff_diff)) == 1
  A, B, C = diff_diff[0], diff[0], sizes[0]
  bb = step_count // m
  return A * bb * (bb - 1) // 2 + B * bb + C


print(solve_hard_interpolate(lines, start, step_count))
