#include <iostream>
#include <vector>

int main() {
    int window = 5; // window size for weighted moving average
    double sum = 0;
    double wav;
    std::vector<int> data = {0, 104, 193, 287, 364, 459, 607, 746, 680, 552, 1023, 465, 433, 420, 377, 340, 295, 250, 215, 185, 850, 150, 117, 75, 38, 12};
    
    std::vector<int> realTimeData = {};
    
    for (int t=0; t < data.size(); t++){
        // weighted moving average algorithm
        realTimeData.push_back(data[t]);
        sum = 0;
        if (t>=window-1){
        // trivial case when size of data > window
            double weightSum = (window*(window+1))/2;
            for (int i=1; i <= window; i++){
                sum += realTimeData[realTimeData.size()-i] * (window - i + 1);
            }
            wav = sum / weightSum;
        } else {
        // edge case when size of data < window
            int useWindow = realTimeData.size();
            double weightSum = (useWindow*(useWindow+1))/2;
            for (int i=1; i <= useWindow; i++){
                sum += realTimeData[realTimeData.size()-i] * (useWindow - i + 1);
            }
            wav = sum / weightSum;
        }
    if(t>0){
        
        int difference = data[t] - wav;
    std::cout << "Time " << t << ", Altitude: " << data[t] << ", WAV: " << wav << ", Difference: " << difference << ", ";
    
        if(difference > -1 && difference < 1){
        // reason for idle bounds in read me
            std::cout << "Idle\n";
        } else if (difference < 0){
            std::cout << "Descending\n";
        } else if (difference > 0){
            std::cout << "Ascending\n";
        }
    
    } else{
        // literally handles the first data point where no comparison can be made lmao 
    std::cout << "Time " << t << " Altitude: " << data[t] << " WAV: " << wav << "\n";
    }
    }
    return 0; // obligatory return 0 
}
