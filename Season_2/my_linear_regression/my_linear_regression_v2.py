

from mpl_toolkits.mplot3d import axes3d
import numpy as np
import matplotlib.pyplot as plt




#********************Introduction**************************

def h(x, theta):
    return np.dot(x, theta)

def mean_squared_error(y_predicted, y_label):
    return np.sum((y_predicted - y_label)**2)/len(y_label)


print("***********************Closed-Form Solution*******************************")
class LeastSquaresRegression():
    def __init__(self,):
        self.theta_ = None 
        
    def fit(self, X, y):
        # Calculates theta that minimizes the MSE and updates self.theta_
        #θ = (XT·X)-1·XT·y
        first_part = np.dot(X.T,X)
        second_part = np.dot(X.T,y)
        self.theta_ = np.dot(np.linalg.inv(first_part),second_part)
    def predict(self, X):
        return h(X, self.theta_)
        # Make predictions for data X, i.e output y = h(X) (See equation in Introduction)


def bias_column(X):
    one_s = np.ones(100).reshape(100,1)
    return np.append(X,one_s, axis= 1)



X = 4 * np.random.rand(100, 1)
y = 10 + 2 * X + np.random.randn(100, 1)
X_new = bias_column(X)

model = LeastSquaresRegression()
model.fit(X_new, y)
print(model.theta_)


y_new = model.predict(X_new)
plt.scatter(X,y)
plt.plot(X,y_new,color= 'red')
plt.show()



print("***********************Gradient Descent*******************************")
class GradientDescentOptimizer():

    def __init__(self, f, fprime, start, learning_rate = 0.1):
        self.f_      = f                       # The function
        self.fprime_ = fprime                  # The gradient of f
        self.current_ = start                  # The current point being evaluated
        self.learning_rate_ = learning_rate    # Does this need a comment ?

        # Save history as attributes
        self.history_ = np.array(start)
    
    def step(self):
        # Take a gradient descent step
        # 1. Compute the new value and update selt.current_
        self.current_ = self.current_ - self.learning_rate_ * f_prime(self.current_) #Grad descent
        # 2. Append the new value to history
        self.history_ = np.append( self.history_,self.current_, axis= 1)
        # Does not return anything

  

        
    def optimize(self, iterations = 100):
        # Use the gradient descent to get closer to the minimum:
        # previous_step_size = np.array([1,1])
        iters = 0
        # For each iteration, take a gradient step
        #while all(previous_step_size > 0.001):
        while iters <= iterations:
            self.step()
            #previous_step_size = abs(self.history_[-1] - self.history_[-2]) #Change in x
            iters += 1
            
    def print_result(self):
        print("Best theta found is " + str(self.current_))
        print("Value of f at this theta: f(theta) = " + str(self.f_(self.current_)))
        print("Value of f prime at this theta: f'(theta) = " + str(self.fprime_(self.current_)))
        return self.history_
    
    def plot_it(self):        
        plt.plot(self.history_[0,:])
        plt.plot(self.history_[1,:])




#f(x) = 3 + (x - (2  6)T)T · (x - (2  6)T)
def f(x):
    a = np.array([[2],[6]])
    t = lambda x: 3 + np.matmul((x - a).T,(x - a))
    return t(x)


def f_prime(x):
    a = np.array([[2],[6]])
    t = lambda x: 2*(x - a)
    return t(x)


grad = GradientDescentOptimizer(f, f_prime, np.random.normal(size=(2,1)), 0.1)
grad.optimize(30)
theta = grad.print_result()
grad.plot_it()


# Set up grid and test data
# x = np.array([[i,i] for i in range(25)])
x1 = np.arange(-10,10,1)
x2 = np.arange(-10,10,1)
X,Y = np.meshgrid(x1,x2)
zs = np.array([x for x in zip(np.ravel(X), np.ravel(Y))])
Z = f(zs.T)
Z = np.diagonal(Z)
Z = np.array(Z).reshape(X.shape)
fig = plt.figure(figsize=(10,8))

x_theta = theta[0,:]
y_theta = theta[1,:]
z_theta = np.diagonal(f(theta))

ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X,Y,Z, color= 'b',alpha= 0.2 )
ax.plot(x_theta,y_theta,z_theta, color= 'k')
ax.scatter(x_theta,y_theta,z_theta, color= 'red')
plt.show()


print("***************Gradient Descent for Linear Regression*************************")

theta_start = np.random.randn(2,1)
X = 4 * np.random.rand(100, 1)
y = 10 + 2 * X + np.random.randn(100, 1)

def gradient_descent(X, m, y, theta_start, iterations = 100, learning_rate = 0.1):
    
    current = theta_start
    history = theta_start
    iters = 0
    while (iters < iterations):
        first_part = np.dot(X,current) - y
        second_part = np.dot(X.T,first_part)
        gradient = 2/m * second_part
        current = current - learning_rate * gradient
        history = np.append(history,current,axis= 1)
        iters += 1
    return history

X_new = np.append(X,np.ones((100,1)),axis= 1)
theta = gradient_descent(X_new, 100, y, theta_start, learning_rate= 0.1)



def h(X,theta):
    return np.dot(X,theta)

plt.plot(X, y, "b.")
plt.grid()
each_10th = 0
for each in theta.T:
    y_predicted = h(X_new, each)
    if (each_10th % 10 == 0):
        plt.plot(X, y_predicted, "r-")
    each_10th += 1
plt.show()






