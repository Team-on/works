# Final Exam
## Question 1: 
Answer: 
```Pipeline 2 is incorrect because $geoNear needs to be the first stage of our pipeline```
```Pipeline 3 fails because $indexStats must be the first stage in a pipeline and may not be used within a $facet```
```Pipeline 1 fails since $out is required to be the last stage of the pipeline```

## Question 2: 
Answer: 
```Pipeline 2 fails because the $divide operator only supports numeric types```
```Pipeline 1 is incorrect because you cannot use an accumulator expression in a $match stage```
```Pipeline 3 is correct and will execute with no error```

## Question 3: 
Answer:
```var pipeline = [{ "$project": { "surname_capital": { "$substr": [{"$arrayElemAt": [ {"$split": [ "$name", " " ] }, 1]}, 0, 1 ] }, "name_size": { "$add" : [{"$strLenCP": "$name"}, -1]}, "name": 1 } }, { "$group": { "_id": "$name_size", "word": { "$push": "$surname_capital" }, "names": {"$push": "$name"} } }, { "$project": { "word": { "$reduce": { "input": "$word", "initialValue": "", "in": { "$concat": ["$$value", "$$this"] } } }, "names": 1 } }, { "$sort": { "_id": 1} } ]```

## Question 4: 
Answer: 
```can not nest a $facet stage as a sub-pipeline.```
```facet_2 uses the output of a parallel sub-pipeline, facet_1, to compute an expression```

## Question 5: 
Answer: 
```var pipeline = [{"$match": { "country": "USA"}}, {"$addFields": { "mean": {"$avg": "$sunnydays"}}}, {"$match": { "mean": {"$gte": 220}, "sunnydays": {"$not": {"$lt": 200 }}}}, {"$sort": {"city": 1}},]```

## Question 6: 
Answer: 
```var pipeline = [ { "$sort": {"name": 1} }, { "$project": {"name":1, "phone": { "$concat": [ {"$arrayElemAt": [{"$split": ["$phone", " "]}, 0]} , "*********" ] }, "ssn": { "$concat": [ "********", {"$arrayElemAt": [{"$split": ["$ssn", "-"]}, 2]} ] } } } ]; db.createView("people_contacts", "people", pipeline);```

## Question 7: 
Answer: 
```OneWorld, with 4 carriers```