# Chapter 2: Authorization and Encryption
## Homework 2.1 : Create Users for Different Tasks
Answer: 
```{"users": [ {"user":"dataLoader","roles":[{"role":"readWriteAnyDatabase","db":"admin"}]}, {"user":"dbAdmin","roles":[{"role":"dbAdminAnyDatabase","db":"admin"}]}, {"user":"sysAdmin","roles":[{"role":"clusterManager","db":"admin"}]}, {"user":"userAdmin","roles":[{"role":"userAdminAnyDatabase","db":"admin"}]} ], "numMembers":3 }```

## Homework 2.2 : Create application specific users
Answer: 
```{ "users": [ {"user":"admin","roles":[{"role":"root","db":"admin"}]}, {"user":"reader","roles":[{"role":"read","db":"acme"}]}, {"user":"writer","roles":[{"role":"readWrite","db":"acme"}]} ], "numMembers":3 }```

## Homework 2.3 : Create custom role
Answer: 
```[ {"role":"EMPLOYEEPORTAL","inheritedRoles":[], "privileges":[{"resource":{"db":"HR","collection":"employees"},"actions":["find","update"]}]},{"role":"HRDEPARTMENT","inheritedRoles":[],"privileges":[{"resource":{"db":"HR","collection":""},"actions":["dropUser","find"]},{"resource":{"db":"HR","collection":"employees"},"actions":["insert"]}]},{"role":"MANAGEMENT","inheritedRoles":[{"role":"dbOwner","db":"HR"}],"privileges":[{"resource":{"db":"HR","collection":""},"actions":["insert"]}]}]```

## Homework 2.4 : Create replica with TLS enabled
Answer: 
```{"numMembers":3}```

## Homework 2.5 : Update replica set nodes to enable encrypted storage engine
Answer: 
```{"doc":{"str":"The quick brown fox jumps over the lazy dog"},"isEnabled":true}```

## Homework 2.6 : Configure KMIP backed mongod
Answer: 
```{isEnabled: true, usingKMIP: true}```