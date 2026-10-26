# mig calorimetry

Finds the final temperature of a coffee-cup calorimetry run by fitting a line to the plateau and extending it back to a vertical line at the mixing time.

- **mig version** tab: sample data from an HCl + Mg / NaOH / NaHCO₃ lab.
- **Import .gambl** tab: load your own Vernier Graphical Analysis file. It is read in your browser and never uploaded.
- **Report sheet** tab: type in masses and temperatures and it fills in the calculated rows of the calorimetry report sheet.
- **Word report** tab: type your cover page, conclusion, a caption for each graph, discussion and post-lab answers, then download a .docx with the graphs two per page and 0.5" margins. Your text is saved in the browser.
- **Download Excel workbook**: builds an .xlsx with a sheet and chart per run (fits done with SLOPE/INTERCEPT formulas), a summary, and the report sheet as live formulas.

Everything is in `index.html`, with no dependencies, and it works offline. How it works: [HOW-IT-WORKS.md](HOW-IT-WORKS.md).
