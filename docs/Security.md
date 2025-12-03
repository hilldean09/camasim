# Security Policy
CAMASIM, as of now, will not utilise any higher privileges, will not utilise any external connections, and is not intended for external implementation. CAMASIM's core functionality will prioritise performance above all else. As a result, external threat models will be considered as an afterthought. 

# Dependencies
Comprised dependencies will be considered as a non-negligible threat model. Trusted dependencies, will be considered as the following:
- C++, CUDA, and Python standard libraries,
- Numpy

Untrusted dependencies will audited where possible. In the case of auditing being impossible or too great a task, this will be noted in [[README]].

# Integrity
CAMASIM's largest priority in regard to security is code integrity, and especially memory safety as in large (and long) simulation this can be very costly. Henceforth, memory safety checks will be included as frequent and non-negotiable in testing and memory related issues will be given the highest priority.