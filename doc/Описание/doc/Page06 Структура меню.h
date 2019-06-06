/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \page page6 ��������� ����

    \tableofcontents

    \section section601 �������

    \code

    |   �������   |
    +------+------+
           |
           +------| ����������� |.............| ������ | ����� |
           |                    
           +------|   ������    |
           |      +------+------+
           |             |
           |             +------| ����������  |.............| ����          | 2          | 4 | 8 | 16 | 32 | 64 | 128 | ������������� |
           |             |                    
           |             +------| �����       |.............| �� ���������� | ���������� |
           |             |
           |             +------| ��������    |
           |
           |
           +------|   ������    |
           |      +------+------+
           |             |
           |             +------| ����������  |.............| ����  | 2              | 4       | 8       | 16      | 32      | 64      | 128     | 256     | 512      |
           |             |
           |             +------| �����       |.............| ����� | �������������� |
           |             
           +------| ��� ����    |.............| ����  | 2       | 4       | 8       | 16      | 32      | 64      | 128     |
           |                                          
           +------| �����       |.............| ����  | 2 ����� | 3 ����� | 4 ����� | 5 ����� | 6 ����� | 7 ����� | 8 ����� | 9 ����� | 10 ����� |
           |                                          
           +------| ������� ��� |.............| 25    | 10      | 5       | 2       | 1       |
           |             
           +------|    �����    |
           |      +------+------+
           |             |
           |             +------| ���         |.............| ��� 1 | ��� 2 | ��� 3 | ��� 4 |
           |             |
           |             +------| �������     |.............[0...100]
           |              
           +------| ��������    |.............| ���������� | ������� |
           |
           +--------------------|  ���������
           |                    +------+------+
           |                           |
           |                           +------|    �����    |
           |                           |      +------+------+
           |                           |             |
           |                           |             +------| C�������
           |                           |             |
           |                           |             +------| �������� �� |.............| ����� 1 | C���� 2 |
           |                           |             |
           |                           |             +------| ����� 1
           |                           |             |
           |                           |             +------| ����� 2
           |                           |             |
           |                           |             +------| �����
           |                           |             |
           |                           |             +------| ���         |.............| ׸����  | �����   |
           |                           |
           |                           +------| �������     |.............[0...100]
           |                           |
           |                           +------| ������
           |                           |
           |                           +------| �����
           |                           |
           |                           +------| ������ ���� |.............| �������� | ������ | ������� |

    \endcode

    \section section602 ����� 1

    \section section603 ����� 2

    \section section604 �����

    \section section605 ����

    \section section606 �������

    \code

    |   �������   |
    +------+------+
           |
           +------| ����������  |
           |      +------+------+
           |             |
           |             +------| �����       |.............| U=    | U~     | I=      | I~     | R | VD | BELL |
           |             |                    
           |             +------| ������      |.............| 2 �   | 50 �   | 500 �   |          *** ����� - U=   ***
           |             |                                  | 2 �   | 40 �   | 400 �   |          *** ����� - U~   ***
           |             |                                  | 2 ��� | 20 ��� | 200 ��� | 10 ��� | *** ����� - R    ***
           |             |                                  --- ��������� ---                     *** ����� - VD   ***
           |             |                                  --- ��������� ---                     *** ����� - BELL ***
           |             |
           |             +------| ���         |.............| ����  | ���    |
           |
           |
           +------| ����������  |
           |      +------+------+
           |             |
           |             +------| ����������� |.............| ����    | ���   |
           |             |
           |             +------| ����� ����� |.............| 100 ��  | 1 c   | 10  c  |
           |             |
           |             +------|����� �������|.............| 100 ��� | 1 ��� | 10 ��� | 100 ��� |
           |             |
           |             +------| ��� ��������|.............| 1       | 10    | 100    |
           |
           |
           +------| ����������� |
           |      +------+------+
           |             |
           |             +------| ������      |.............| ���� | ��� |
           |             |
           |             |
           |             +------| ��������    |
           |             |      +------+------+
           |             |             |
           |             |             +------| ����� 1     |.............| ���� | ��� |
           |             |             |
           |             |             +------| ����� 2     |.............| ���� | ��� |
           |             |             |
           |             |             +------| ������      |.............| ���� | ��� |
           |             |             
           |             |
           |             +------|   ������    |
           |             |      +------+------+
           |             |             |
           |             |             +------| ��������� � |.............| USB-PC | USB-Flash |
           |             |
           |             |
           |             +------|  ��������   |
           |                    +------+------+
           |                           |
           |                           +------| ��������    |.............| USB-PC | USB-Flash |
           |
           |
           +------|   ������    |
           |      +------+------+
           |             |
           |             +------| ����������� |.............| ����        | ���      |
           |             |
           |             +------| �����       |.............| ��������    | �������� |
           |             |
           |             +------| ��������    |.............| ����� 1 + 2 | ����� 1  | ����� 2 |
           |             |
           |             +------| ����        |.............| ��������    | �������� | �����   | ����������� |
           |             |
           |             +------|   �������   |
           |                    +------+------+
           |      
           |      
           |
           |      
           +------|  T�����-�   |
                  +------+------+
                         |
                         +------| ����������  |.............| ���������� | ���    |
                         |
                         +------| ���         |.............| 100 ��     | 500 �� | *** ���������� - ���������� ***
                         |                                  | 4 ��       | 20 ��  | *** ���������� - ���        ***
                         |
                         +------| ����������  |.............| +          | -      |
                         |
                         +------| ����������� |.............| �����      | �����  |
                         |
                         +------| ����������� |.............| 1          | 2      | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |

    \endcode

    \section section607 �����

    \code

    |   �������   |
    +------+------+
           |
           |
           +------|   �������   |
           |      +------+------+
           |             |
           |             +------| ����������  |.............| ���  | �� |
           |             |
           |             +------| ������ 1 �  |.............| ���� | ���������� | ����� | ���������� � ����� |
           |             |
           |             +------| ������ 2 �  |.............| ���� | ���������� | ����� | ���������� � ����� |
           |             |
           |             +------| 1/dT        |.............| ���� | ��� |
           |             |
           |             +------|  ���������� |
           |                    +------+------+
           |                           |
           |                           +------|             |
           |
           +------|   �������   |
                  +------+------+
                         |
                         +------| ����������  |.............| ��� | �� |
                         |
                         +------| ����������  |.............| 1   | 2  | 1x5   | 2x5 | 3x5 | 6x1 | 6x2 |
                         |
                         +------| ������      |.............| 1   | 2  | 1 � 2 |
                         |
                         +------|  ���������  |
                                +------+------+
                                       |
                                       +------|             |


    \code

    \section section608 ������

    \section section609 ������

*/
