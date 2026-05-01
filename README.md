1. Project Members
    - Samuel Habib (smh389)
    - Victor Peng (vmp134)

2. Testing Plan
    - Unit Tests (testing.c)
        - 
    - Integration Tests (./chatd and ./raw)
        - 
    
3. Design Plan
    - Clients and Polling
        - For each client, we made a struct with their data
            - We store their file descriptor, name, status, and state
            - State determines if they have connected (0) or if they have logged in (1)
        - We decided to implement a LinkedList of clients
            - This avoids array sorting and shifting, as we are dealing with pointers
            - Simple removal of clients
        - We declare pollfd fds (Ln 28) as a temporary array capable of housing up to SOMAXCONN
            - We iterate through our LinkedList to gather fds
            - If we delete a node, it simply does not show up
            - Avoid shifting whenever a client disconnects
    - Message Handling
        - 
    - Memory Handling
        - 