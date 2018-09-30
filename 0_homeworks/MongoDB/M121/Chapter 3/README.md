# Chapter 3: Core Aggregation - Combining Information
## Lab - $group and Accumulators
Answer: 
```{ "highest_rating" : 9.2, "lowest_rating" : 4.5, "average_rating" : 7.5270, "deviation" : 0.5988 }```

## Lab - $unwind
Answer: 
```{ "_id" : "John Wayne", "numFilms" : 107, "average" : 6.4 }```

## Lab - Using $lookup
Answer: 
```"SkyTeam"```

## Lab: $graphLookup
Answer: 
```db.air_alliances.aggregate([{ $match: { name: "OneWorld" } }, { $graphLookup: { startWith: "$airlines", from: "air_airlines", connectFromField: "name", connectToField: "name", as: "airlines", maxDepth: 0, restrictSearchWithMatch: { country: { $in: ["Germany", "Spain", "Canada"] } } } }, { $graphLookup: { startWith: "$airlines.base", from: "air_routes", connectFromField: "dst_airport", connectToField: "src_airport", as: "connections", maxDepth: 1 } }, { $project: { validAirlines: "$airlines.name", "connections.dst_airport": 1, "connections.airline.name": 1 } }, { $unwind: "$connections" }, { $project: { isValid: { $in: ["$connections.airline.name", "$validAirlines"] }, "connections.dst_airport": 1 } }, { $match: { isValid: true } }, { $group: { _id: "$connections.dst_airport" } } ])```