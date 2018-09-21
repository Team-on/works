# Chapter 1: Authentication
## Homework 1.1 : Enable SCRAM-SHA-1 
Answers: 


```mongo admin -u alice -p secret --eval "db.runCommand({getParameter: 1, authenticationMechanisms: 1})"```


```mongo -u alice -p secret --eval "db=db.getSisterDB('admin');db.runCommand({getParameter: 1, authenticationMechanisms: 1})" --authenticationDatabase admin```


```mongo admin --eval "db.auth('alice', 'secret');db.runCommand({getParameter: 1, authenticationMechanisms: 1})"```

## Homework 1.2 : Enabling Authentication on a Running Replica Set
Answer: 
```{ unauthorizedStatus: { "ok" : 0, "errmsg" : "not authorized on admin to execute command { replSetGetStatus: 1.0 }", "code" : 13 }, memberStatuses: ["PRIMARY","SECONDARY","SECONDARY"] }```

## Homework 1.3: Enabling Internal Authentication using X.509
Answer: 
```{ unauthorizedStatus: { "ok" : 0, "errmsg" : "not authorized on admin to execute command { replSetGetStatus: 1.0 }", "code" : 13 }, memberStatuses: ["PRIMARY","SECONDARY","SECONDARY"] }```

## Homework 1.4: Migrating MONGODB-CR to SCRAM-SHA-1
Answer: 
```[ "SCRAM-SHA-1" ]```

## Homework 1.5: Enabling Mixed Authentication Mechanisms
Answer: 
```{ unauthorizedStatus: { "ok" : 0, "errmsg" : "not authorized on admin to execute command { replSetGetStatus: 1.0 }", "code" : 13 }, memberStatuses: ["PRIMARY","SECONDARY","SECONDARY"], users: [{"_id":"admin.will","roles":[{"role":"root","db":"admin"}]},{"_id":"$external.C=US,ST=New York,L=New York City,O=MongoDB,OU=University2,CN=M310 Client","roles":[{"role":"userAdminAnyDatabase","db":"admin"}]}] }```

## Homework 1.6: Enabling LDAP Authentication on a Replica Set
Answer: 
```{ unauthorizedStatus: { "ok" : 0, "errmsg" : "not authorized on admin to execute command { replSetGetStatus: 1.0 }", "code" : 13 }, memberStatuses: ["PRIMARY","SECONDARY","SECONDARY"] }```