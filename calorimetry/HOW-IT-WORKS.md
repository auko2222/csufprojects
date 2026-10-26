# How the calorimetry line-crossing tool works

Tool: open index.html, or the GitHub Pages link for this repo.

## 1. The chemistry: why the lines cross at "final T"

- In a coffee-cup calorimeter, the reaction heats (or cools) the solution, and you measure ΔT to get q = m·c·ΔT.
- The cup starts leaking heat to the room **before the reaction is done**. So the highest reading you see is a little too low.
- Fix: draw a line through the steep rise and a line through the slow cooling after the peak. Extend both lines until they cross. The temperature where they cross is about what you would have reached if the heat had all been released instantly, with no leak. That is the "final T".
- For an endothermic run (NaHCO₃ + HCl) it is the same idea flipped: a falling line and a slowly warming line.

## 2. The file: what a .gambl actually is

- `.gambl` = Vernier Graphical Analysis file. It is a **tar archive**, a bundle of files like a .zip.
- Inside is one file, `vstudm/data.udm`, which is plain-text **XML** (text with nested `<tags>`, like HTML).
- Structure: the Document holds 5 **DataSets** (one per run). Each DataSet holds 2 **DataColumns** (Time and Temperature). Each column holds a list of numbers.
- Pair the lists in order (1st time with 1st temperature, and so on) and you get the data points.
- Most of the rest of the file is graph settings, like axis ranges and colors.

## 3. The data

- The probe took a reading every **0.5 s** for about 5 min, so each run has about 600 points (5 × 60 ÷ 0.5). The 5 runs total 3,068 points.
- Each point is (time in s, temperature in °C), for example (0.0, 20.61), (0.5, 20.60), and so on.
- The file stores more decimals than the probe can actually measure (the probe is good to about ±0.2 °C), so values are rounded to 2 places.

## 4. Getting the numbers out (Python)

- `tar xf file.gambl` unpacks it.
- A short Python script uses `xml.etree.ElementTree` (Python's built-in XML reader) to loop over each DataSet, find the Time and Temperature columns, and turn the text into lists of numbers.
- The lists were saved as JSON (a simple text format for data) and built right into the web page, so the page doesn't need the original file.

## 5. The best-fit line (least squares)

A line is T = m·t + b, where m is the slope (°C per second) and b is the value of T at t = 0.

"Least squares" picks the m and b that make the line as close as possible to all the points. It does this by minimizing the sum of the squared vertical gaps between the points and the line. It is the same thing as Excel's LINEST or "Linear Fit" in Graphical Analysis.

    m = Σ (t − t̄)(T − T̄)  /  Σ (t − t̄)²
    b = T̄ − m·t̄

t̄ and T̄ are the averages of the points used.

### Why it matches Excel exactly

- Excel's `SLOPE`, `INTERCEPT`, `LINEST` and the "Linear" trendline all use these same two formulas. So does Graphical Analysis's Linear Fit.
- For a given set of points there is only **one** least-squares line. The formulas have one exact answer, not an estimate that depends on the program. Any program that does least squares correctly has to land on the same m and b, give or take rounding in the last decimal.
- The only thing that can differ is **which points you give it**. Same points in, same line out.

**Check it yourself (Trial 1):** export the run to CSV from Graphical Analysis (or copy the table) and put time in column A and temperature in column B, with a header in row 1. Then:

    Rise:     =SLOPE(B47:B84, A47:A84)       → 0.5247
              =INTERCEPT(B47:B84, A47:A84)   → 13.57     (rows = 22.5 s to 41 s)
    Plateau:  =SLOPE(B235:B625, A235:A625)   → −0.0115
              =INTERCEPT(B235:B625, A235:A625) → 39.90   (rows = 116.5 s to 311.5 s)
    Cross t:  =(D4−D2)/(D1−D3) → 49.1   (if the four results above are in D1, D2, D3, D4)

## 6. Where the lines cross

Rise line: T = m1·t + b1. Plateau line: T = m2·t + b2.

    m1·t + b1 = m2·t + b2
    m1·t − m2·t = b2 − b1
    t = (b2 − b1) / (m1 − m2)

Plug that t into either line to get final T.

Trial 1: t = (39.90 − 13.57) / (0.5247 + 0.0115) = 49.1 s, and T = 0.5247(49.1) + 13.57 = 39.3 °C.

## 7. Which points go into each line

These are rules of thumb, chosen to keep each line on a straight part of the curve:
- **Rise:** points between 25% and 75% of the way from initial T to the peak. The ends of the climb are curved: at the start the reaction is just getting going, and at the top it runs out of Mg.
- **Plateau:** from 30 s after the peak to the end of the run. This skips the rounded top.
- **Initial T:** the average of the flat readings before the temperature moves 0.3 °C.

The cutoffs are choices, not rules. Changing them moves final T by about ±0.1–0.2 °C for most runs, and by about ±0.5 °C for Trial 1 (it has a bump near the peak).

## 8. The web page

- It is one HTML file with JavaScript, hosted as a Claude artifact.
- The chart is drawn with SVG (shapes the browser draws from coordinates). No charting library is used.
- When you type new ranges, the page re-runs the least-squares fit and the crossing math in your browser.
- Dragging on the chart uses "pointer events", which work for both touch and mouse. The page finds the nearest data point to your finger and shows its values.

## 9. Saying it straight

Be upfront that you built this with Claude. What you can honestly say is that you understand what every step does: unpack the file, read the XML, fit two least-squares lines, solve for where they cross. If someone asks a question about the code you can't answer, "I had AI write the code, but here's what it does" is a fine answer.

## Likely questions

- **"Why not just use the max?"** Heat leaks out during the reaction, so the max underestimates the temperature change. The crossing corrects for that.
- **"How do you know the fit ranges are right?"** You don't know for sure. They're a judgment call. I checked 25 different choices, and the answers barely moved (except Trial 1, ±0.5 °C).
- **"Could Graphical Analysis do this?"** Yes. You'd put a linear fit on each region and solve for the crossing by hand. The tool just does it faster and shows the algebra.
- **"Where's the data from?"** The Vernier temperature probe file from lab, read directly. Nothing was typed in by hand.
