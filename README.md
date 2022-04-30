# human-development-index-india
Design and Development of a Statistical Model for Ranking of a territory using Machine Learning Algorithms

We as a nation have come a long way since independence and have to go a long way. Human Development Index (HDI) and other indexes are a good way to track the performance of a country/state but are very narrow-in their choice of factors selected for comparison & score calculation. Almost all indexes originate in west and their methodology do not translate well for countries like India. We devised a home grown multi dimensional method for comparison. We generated rankings based on scores between states which will include a wide variety of measures and factors to indicate the quality of life being provided in different states of the country. This will also provide a perspective to learn from the best performing states and implement those learnings to worst performing states.

### Methodology

Step 1 - Collection of required data from verified sources.<br>
Step 2 - Cleaning of data and replacing 0 or null values with most suitable values like mean or mode from dataset.
Step 3 - Assigning weights after calculation using FAHP model (explained in later slides).
Step 4 - Reading data from datasets, multiplying weights with data values and adding them to calculate score.
Step 5 - Aggregating scores and normalizing them to get a final score between 1-10.
Step 6 - Ranking states based on their cumulative scores and grading them.
Step 7 - Creating &  showing graphs using graphics.h.

### Datasets Used

*Health –
		- Life Expectancy		- Infant Mortality Rate
*Education –
    - Literacy Rate		- Dropout Rate
*Economy –
		- Unemployment Rate		- Income per capita
*Crime –
		- Murder		- Rape		- Minor		- Major


### Future Scope

In future we can extend and include following functions –
*Adding data of multiple years for state wise as well as year wise comparison.
*Adding GUI so that user can himself select which states and parameters to compare
*Extending the index from only Indian states to other countries as well.
*Taking preference from user so as to generate personalized weights and rankings as required by user’s preference.

### Application

*Comparing different parts of the country
*Comparing states and making decision on where to move for better living
*Understanding why a state is performing better in any particular field and apply it to other states as well
*Deciding whether a Government/Party is worth re-electing.
*New broad spectrum methodology which can be used in other home grown indexes also. 
*World indexes (in future).

