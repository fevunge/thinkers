*This project has been created as part of the 42 curriculum by fevunge*

# Philosophers

## Overview

This program was written in C, in accordance with the standards of the school network 42.  

Here are the key things you need to know to succeed in this assignment:  
- One or more philosophers sit at a round table.  
	There is a large bowl of spaghetti in the middle of the table.
---
- The philosophers take turns **eating**, **thinking**, and **sleeping**.  
	- *While they are eating* - they are not thinking **nor** sleeping;  
		```python
			if philosopher.is_eating():
				philosopher.set_thinking(false)
				philosopher.set_sleeping(false)
		```
	- *while they are thinking* - they are not eating **nor** sleeping;  
		```python
			if philosopher.is_thinking():
				philosopher.set_eating(false)
				philosopher.set_sleeping(false)
		```
	- *while they are sleeping* - they are not eating **nor** thinking.  
		```python
			if	philosopher.is_sleeping()) :
				philosopher.set_eating(false)
				philosopher.set_thinking(false)
		```
---
- There are also forks on the table. There are as many forks as philosophers. 
	```python
		>>> table.get_forks().amount == table.get_philosophers().amount
		True
	```
	---
- Since eating spaghetti with just one fork is impractical, a philosopher must pick up  
	both the fork to their right and the fork to their left before eating.
---
- When a philosopher has finished eating, they put their forks back on the table and  
	start sleeping. Once awake, they start thinking again. The simulation stops when  
	a philosopher dies of starvation.  
---
- Every philosopher needs to eat and should never starve.  
---
- Philosophers do not communicate with each other.  
---
- Philosophers do not know if another philosopher is about to die.  
---


## Description

## Instructions 

## Resource  


